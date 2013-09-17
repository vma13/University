class ApplicationController < ActionController::Base
  include AuthenticatedSystem
  before_filter :authenticate
  protect_from_forgery  
  private
  
  def admin_permition
  unless @current_user.admin?
   render :text => "Permition denied",:layout=>"application"
   end
  end

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
