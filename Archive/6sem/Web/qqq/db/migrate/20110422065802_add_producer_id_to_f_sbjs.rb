class AddProducerIdToFSbjs < ActiveRecord::Migration
  def self.up
    add_column :f_sbjs,:producer_id,:integer
  end

  def self.down
   remove_column :f_sbjs,:producer_id
  end
end
