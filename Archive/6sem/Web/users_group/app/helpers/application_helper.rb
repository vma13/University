module ApplicationHelper

def footer_years
	start="2009"
	cur_year=Time.now.year
	if cur_year==start
		return start
	end
	return "#{start} - #{cur_year}"
end

end
