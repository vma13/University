include Math

@population = []
@new_population = []
@n = 70
@p_c = 0.3
@p_m = 0.7

class Individ
  def initialize(set)
    @set = set
    @adaptation = nil
    @normal_adapt = nil
  end
  attr_accessor :set, :adaptation, :normal_adapt
end

def print_adaptation(population)
	for i in 0...population.size
		print population[i].adaptation; print " ";
	end
	puts
end

def print_population(population)
	for i in 0...population.size
		print population[i].adaptation
		print " "
		print population[i].set
		puts
	end
	puts
end

def check(problem)
	h = 0
	for i in 0...problem.size
		for j in i+1...problem.size
			if problem[i] == problem[j]
				h += 1
			end
			if problem[i] + i == problem[j] + j
				h += 1
			end
			if problem[j] - problem[i] == j - i 
				h += 1
			end
		end	
	end
	return 28-h
end

def create_population()
	for n in 0...@n
		problem = Array.new(8)
		for i in 0...problem.size
			problem[i] = rand(8)
		end
		@population[n] = Individ.new(problem)
	end
end

def normaliz_adaptation()
	sum = 0
#	for i in 0...@population.size
#		sum += @population[i].adaptation
#	end
	@population.each{|x| sum += x.adaptation}
	for i in 0...@population.size
		@population[i].normal_adapt = @population[i].adaptation / sum.to_f
		if i > 0 
			@population[i].normal_adapt += @population[i-1].normal_adapt
		end
	end
end

def find_avg_adaptation(population)
	sum = 0
	population.each{|x| sum += x.adaptation}
	return sum/population.size.to_f 
end
def find_best_individ()
	r = rand; 
	for i in 0...@population.size
		if r < @population[i].normal_adapt
			return i
		end
	end
end

def	crossing(first_number,second_number)
	first = Array.new
	second = Array.new
	for i in 0...8
		first << @population[first_number].set[i]
		second << @population[second_number].set[i]
	end
	if rand < @p_c
		x = rand(6) + 1		
		for i in x...first.size
			first[i],second[i] = first[i],second[i]
		end
	end
	if rand < @p_m
		first[rand(8)] = rand(8)
		second[rand(8)] = rand(8)
	end

	@new_population << Individ.new(first)
	@new_population[-1].adaptation = check(@new_population[-1].set)
	@new_population << Individ.new(second)
	@new_population[-1].adaptation = check(@new_population[-1].set)
end

def copy_population(population,number)
	individ = Individ.new(population[number].set)
	individ.adaptation = population[number].adaptation
	individ.normal_adapt = population[number].normal_adapt
	return individ
end
def print_board(problem)
	for i in 0...problem.size
		print " "
		for j in 0...problem[i]
			print "  | "
		end
		print "Q"; print " | "; 
		for j in problem[i]+1...problem.size
			print "  | "
		end
		if i != problem.size-1
			puts;print "-----------------------------------";
		else
			puts
		end
		puts
	end
end

def genetic()
	create_population()
	for i in 0...@n
		@population[i].adaptation = check(@population[i].set)
	end
	k = 0
	number = -1
	stop = false
	while !stop
		normaliz_adaptation()
		#print_adaptation()
		avg_adaptation = find_avg_adaptation(@population)
		print k; print " | Adaptation = "; print avg_adaptation; puts
		for n in 0...@n/2
			first_number = find_best_individ()
			while (first_number == (second_number = find_best_individ()));	end
			crossing(first_number,second_number)
		end
		for i in 0...@new_population.size
			if @new_population[i].adaptation == 28
				stop = true
				print "Yraaa!"; puts
				number = i
			end
		end
		@population = []
		for i in 0...@new_population.size
			@population << copy_population(@new_population,i);
		end
		@new_population = []
		k += 1
	end
	puts k
	print_adaptation(@population)
	print_board(@population[number].set);
end

genetic()
