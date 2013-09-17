class CreateFSbjs < ActiveRecord::Migration
  def self.up
    create_table :f_sbjs do |t|
      t.string :name

      t.timestamps
    end
  end

  def self.down
    drop_table :f_sbjs
  end
end
