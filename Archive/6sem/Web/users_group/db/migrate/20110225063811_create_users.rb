class CreateUsers < ActiveRecord::Migration
  def self.up
    create_table :users do |t|
      t.string :login
      t.string :password_salt
      t.string :password_hashed
      t.string :name
      t.string :email
      t.integer :role
      t.boolean :ban

      t.timestamps
    end
  end

  def self.down
    drop_table :users
  end
end
