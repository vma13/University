class ApplicationController < ActionController::Base
  include AuthenticatedSystem
  
  protect_from_forgery
  before_filter :authenticate
  private

  def authenticate
    #authenticate_or_request_with_http_basic do |user_name, password|
     # user_name == "admin" && password == "qwerty"
    @current_user = current_user
    #end
  end

  def check_auth
    redirect_to login_path unless @current_user
  end

end
