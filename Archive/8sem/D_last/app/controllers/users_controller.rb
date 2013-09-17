# -*- coding: utf-8 -*-
class UsersController < ApplicationController
  before_filter :check_admin_user

  def change_user_password
    user = User.authenticate(@current_user.login, params[:old_password])
    if user
      if (params[:password] == params[:password_confirmation]) && !params[:password_confirmation].blank?
        @current_user.password_confirmation = params[:password_confirmation]
        @current_user.password = params[:password]
        if @current_user.save
          flash[:notice] = "Пароль успешно изменен."
          redirect_to user
        end
      else
        flash[:alert] = "Пароли не совпадают."
      end
    else
      flash[:alert] = "Вы ввели неправильный пароль." 
    end
  end
  
  def change_session_year
    session[:choice_year] = params[:chosen_year].to_i
    render :nothing => true
  end

  def index
    @users = User.page(params[:page])
  end

  def show
    @user = User.find(params[:id])
  end

  def new
    @user = User.new
  end
  
  def edit
    @user = User.find(params[:id])
  end

  def create
    logout_keeping_session!
    @user = User.new(params[:user])
    success = @user && @user.save
    if success && @user.errors.empty?
      self.current_user = @user
      flash[:notice] = "Регистрация успешно завершена"
      redirect_to root_path
    else
      flash.now[:error]  = "При регистрации произошли ошибки."
      render :action => 'new'
    end
  end

  def update
    @user = User.find(params[:id])
    if @user.update_attributes(params[:user])
      redirect_to @user, :notice=>'Пользователь сохранен.'
    else
      render :action => "edit"
    end
  end

  def destroy
    user = User.find(params[:id])
    login = user.login
    if @current_user.id == user.id
      user.destroy
      render 'sessions/new', :layout => 'login'
    else
      user.destroy
      redirect_to users_url, :notice => 'Пользователь:' + login + ' удален.'
    end
  end
end

