# -*- coding: utf-8 -*-
class ApplicationController < ActionController::Base
  include AuthenticatedSystem

  protect_from_forgery
  before_filter :authenticate
  private

  def authenticate    
    @current_user = current_user
  end

  def check_auth
     redirect_to login_path unless @current_user   
  end

end
