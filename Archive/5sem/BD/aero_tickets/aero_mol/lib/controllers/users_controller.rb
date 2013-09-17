class UsersController < Controller

  def is_authorized_action?()
    !([:registration].include?(@action))
  end

	##true when mail is incorrect
	def wrong_mail(mail)
		return (mail =~ /.+@.+[.].+/) != 0
	end

	##true when wrong data
	def wrong_data(string)
		return (string.size < 5 or string.size > 16)
	end

	def is_admin?()
		return User.is_administrator(@db, @user)
	end

	##register a user
  def registration()
    if @cgi.params.has_key?('is_commit')
			if !(@cgi.params.has_key?('login') and @cgi.params['login'][0] != '' and @cgi.params.has_key?('password') and @cgi.params['password'][0] != '' and @cgi.params.has_key?('password1') and @cgi.params['password1'][0] != '')
				@message = 'Не все данные введены'
      elsif @cgi.params['password'][0] != @cgi.params['password1'][0]
				@message = 'Пароли не совпадают'
			elsif User.check_user_for_registration(@db, @cgi.params['login'][0])
				@message = 'Пользователь с таким логином существует'
			elsif wrong_data(@cgi.params['login'][0]) or wrong_data(@cgi.params['password'][0])
				@message = 'Неправильный размер логин и пароля'
			elsif @cgi.params['mail'][0] != '' and wrong_mail(@cgi.params['mail'][0])
				@message = 'Неверный e-mail'
			else
        @header = 'Создание завершено'
				User.add(@db, @cgi.params['login'][0], @cgi.params['password'][0], (@cgi.params['mail'][0] == '' ? nil : @cgi.params['mail'][0]) )
			end
    else
      @header = 'Введите данные'
    end
    render_template('registration')
  end

	##personal cabinet
	def personal_cab()
		if @cgi.params.has_key?('is_commit')

			if @cgi.params.has_key?('delete')
				@message = 'Пользователь удален'
				User.delete(@db, @user)
		    @session.delete()
		    @session = nil
			end

			if @cgi.params.has_key?('new_mail') and @cgi.params['new_mail'][0] != ''
				if wrong_mail(@cgi.params['new_mail'][0])
					@message = 'Неверный email'
				else
					@message = 'Email обновлён'
					User.update_mail(@db, @user, @cgi.params['new_mail'][0])
				end
			end

			if @cgi.params.has_key?('new_password') and @cgi.params['new_password'][0] != ''
				if wrong_data(@cgi.params['new_password'][0])
					@message = 'Неверный пароль'
				else
					@message = 'Пароль обновлён'
					User.update_pass(@db, @user, @cgi.params['new_mail'][0])
				end
			end 

		end
		if is_admin?()
			@items = User.find_all(@db)
			render_template('personal_cab_admin')
		else
			render_template('personal_cab')
		end
	end

  def UsersController.actions(user)
		result = []
    #unless user.nil?
    #  result = [[:personal_cab, 'Личный кабинет']]
    #end
    result
  end

end
