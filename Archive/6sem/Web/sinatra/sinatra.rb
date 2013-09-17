require "sinatra"
require "erb"
#encoding: utf-8
get "/" do
@teams = %w(Spartak Dinamo CSKA Zenit Lokomotiv Rubin)
erb :index
  end 


post "/Scores" do
params.inspect
end
