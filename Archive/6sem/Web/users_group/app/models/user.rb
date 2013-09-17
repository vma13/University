require 'digest/sha2'

class User < ActiveRecord::Base
	validates :login, :presence=>true, :uniqueness=>true, :length=>{:minimum=>4, :maximum=>20}
	validates :name, :presence=>true, :length=>{:minimum=>3}
	validates :password_hashed, :presence=>true
	validates :password_salt, :presence=>true
	validates :email, :presence=>true, :length=>{:minimum=>6}, :uniqueness=>true, :format=>{:with=>/\A[a-z\-]{3,}\d*@(mail\.)?msiu\.ru\Z/i}
	validates :password, :confirmation=>true
	validates :role, :inclusion=>{:in=>0..1}
	#attr_accessor :password, :password_confirmation
	attr_accessor :password_confirmation
	attr_reader :password
	def password=(password)
		@password=password
		if !password.blank?
			generate_salt
			self.password_hashed = self.class.encrypt_password(password, password_salt)
		end
	end
	def User.encrypt_password(password, salt)
		Digest::SHA2.hexdigest(password+"ooooops"+salt)
	end
	private
	def generate_salt
		self.password_salt=self.object_id.to_s+rand.to_s
	end
end
