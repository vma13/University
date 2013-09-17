# -*- coding: utf-8 -*-
class ApplicationController < ActionController::Base
  require File.join(Rails.root, 'lib', 'authenticated_system.rb')
  include AuthenticatedSystem
  #protect_from_forgery

  before_filter :check_user

  private
  def check_user
    @current_user = current_user
  end
  
  def check_teacher_user
    unless @current_user && ( @current_user.admin? || @current_user.teacher? || @current_user.regular?)  
      render :text=>"Доступ запрещён", :layout => 'application'
    end
  end

  def check_regular_user
    unless @current_user
      render 'sessions/new', :layout => 'login'
      #render :text=>"Доступ для незарегистрированных пользователей запрещен", :layout => 'application'
    end
  end

  def check_admin_user
    unless @current_user && @current_user.admin?
      render :text=>"Доступ", :layout => 'application'
    end
  end
end


  def change_session_year(chouse)
    if !chouse.blank?
      session[:chouse_year] = chouse
    end
  end

