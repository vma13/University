# -*- coding: utf-8 -*-
# This controller handles the login/logout function of the site.  
class SessionsController < ApplicationController
  # Be sure to include AuthenticationSystem in Application Controller instead
  include AuthenticatedSystem

  # render new.rhtml
  def new
  end

  def create
    logout_keeping_session!
    user = User.authenticate(params[:login], params[:password])
    session[:choice_year] = Time.now.year
    if user
      # Protects against session fixation attacks, causes request forgery
      # protection if user resubmits an earlier form using back
      # button. Uncomment if you understand the tradeoffs.
      # reset_session
      self.current_user = user
      new_cookie_flag = (params[:remember_me] == "1")
      handle_remember_cookie! new_cookie_flag
      flash[:notice]="Вход выполнен"
      redirect_to schoolkids_path
    else
      note_failed_signin
      @login       = params[:login]
      @remember_me = params[:remember_me]
      render :action => 'new', :layout => 'login'
    end
  end

  def destroy
    logout_killing_session!
    session[:choice_year] = nil
    render 'sessions/new', :layout => 'login'
    #redirect_back_or_default('/', :notice => "Выход выполнен.")
  end

protected
  # Track failed login attempts
  def note_failed_signin
    flash.now[:error] = "Неудачная попытка авторизации под именем пользователя '#{params[:login]}'"
    logger.warn "Failed login for '#{params[:login]}' from #{request.remote_ip} at #{Time.now.utc}"
  end
end
