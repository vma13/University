#encoding: utf-8 
require 'digest/sha1'

class User < ActiveRecord::Base
  include Authentication
  include Authentication::ByPassword
  include Authentication::ByCookieToken
  
  default_scope order(:login)
  paginates_per 10

  set_table_name 'users'

  ROLES=["Пользователь", "Администратор", "Преподаватель"]
  
  validates_format_of :password, :with => /^([\x20-\x7E]){4,16}$/,
    :message => "Должен быть от 4 до 16 симолов",
    :unless => :password_is_not_being_updated?

  validates :login, :presence   => true,
                    :uniqueness => true,
                    :length     => { :within => 3..40 },
                    :format     => { :with => Authentication.login_regex, :message => Authentication.bad_login_message }
  
  validates :email, :presence   => true,
                    :uniqueness => true,
                    :format     => { :with => Authentication.email_regex, :message => Authentication.bad_email_message },
                    :length     => { :within => 6..100 }

  validates :role,:presence=>true,:inclusion => {:in=>0...ROLES.size}

  # HACK HACK HACK -- how to do attr_accessible from here?
  # prevents a user from submitting a crafted form that bypasses activation
  # anything else you want your user to change should be added here.
  attr_accessible :login, :email, :name, :password, :password_confirmation, :year, :old_pass, :role



  # Authenticates a user by their login name and unencrypted password.  Returns the user or nil.
  #
  # uff.  this is really an authorization, not authentication routine.  
  # We really need a Dispatch Chain here or something.
  # This will also let us return a human error message.
  #
  
  before_save :scrub_login
  after_save :flush_passwords
  
  def scrub_login
    self.login.downcase!
  end
  
  def flush_passwords
    @password = @password_confirmation = nil
  end
  
  def password_is_not_being_updated?
    self.id and self.password.blank?
  end

  def self.authenticate(login, password)
    return nil if login.blank? || password.blank?
    u = find_by_login(login.downcase) # need to get the salt
    u && u.authenticated?(password) ? u : nil
  end

  def eval?
   u = find_by_login(login.downcase)
   
  end

  def login=(value)
    write_attribute :login, (value ? value.downcase : nil)
  end

  def email=(value)
    write_attribute :email, (value ? value.downcase : nil)
  end

  def teacher?
    role==2
  end

  def admin?
    role==1
  end
  
  def regular?
    role==0
  end
  
  def human_role
    ROLES[role]
  end
  
  def pass_generate(len=7) 
  chars = ('a'..'z').to_a + ('A'..'Z').to_a + ('1'..'9').to_a - ['o', 'O', 'i', 'I']
   return Array.new(len) { chars[rand(chars.size)] }.join 
  end 
  
  def old_pass
  end
  
  def old_pass=(val)
  end
  
  protected
    


end
