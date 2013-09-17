default: dbinit dbseed rails

dbinit:
	rake db:drop db:migrate

dbseed: db/seeds.rb
	rake db:seed
rails:
	rails s