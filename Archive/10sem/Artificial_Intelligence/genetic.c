#include <stdio.h> 
#include <malloc.h>
#include <stdlib.h>

int problem[8];
int population[];
int new_population[];
int n = 70;
int p_c = 0.3;
int p_m = 0.7;
int set;
int adaptation;
int normal_adapt;

/*
class Individ
  def initialize(set)
    @set = set
    @adaptation = nil
    @normal_adapt = nil
  end
  attr_accessor :set, :adaptation, :normal_adapt
end
*/

int print_adaptation(population){
int i;
 for (i = 0; i < population.size; i++){
  printf("%d", population[i].adaptation); // переписать
  printf(" ");
 }
}
/*
def print_adaptation(population)
	for i in 0...population.size
		print population[i].adaptation; print " ";
	end
	puts
end
*/

int print_population(population){
int i = 0;
 for (i; i < population.size; i++){
  printf("%d", population[i].adaptation);
  printf(" ");
  printf("%d", population[i].set);
  printf("\n");
 }
 prinf("\n");
}
/*
def print_population(population)
	for i in 0...population.size
		print population[i].adaptation
		print " "
		print population[i].set
		puts
	end
	puts
end
*/

int check(problem){
int h = 0;
int i = 0, j = 0;
 for (i; i < problem.size; i++){
  for (j; j < problem.size; j++){
   if ((problem[i] == problem[j]) || (problem[i] + i == problem[j] + j) || (problem[j] - problem[i] == j - i)){
    h++;
   }
  }
 }
 return 28-h;
}
/*
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
*/

int create_population(void){
int i,k;
 for (k = 0; k < problem.size; k++){
  for (i = 0; i < problem.size; i++){
   problem[i] = rand() % 8;
  }
  population[k] = individ problem; // посмотреть как создать новый элемент класса  
 }
}
/*
def create_population()
	for n in 0...@n
		problem = Array.new(8)
		for i in 0...problem.size
			problem[i] = rand(8)
		end
		@population[n] = Individ.new(problem)
	end
end
*/

int normalize_adaptation(void){
float sum = 0.0;
int i,k;
 for (i = 0; i < population.size; i++){
  sum += population[i].adaptation;
  for (k = 0; k < population.size; k++){
   population[i].normal_adapt = population[i].adaptation / sum; //(переписать to_f)
   if (k < 0){
    population[i].normal_adapt += population[i-1].normal_adapt;
   }
  }
 }
}
/*
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
*/

int find_average_adaptation(population){
int i;
float sum = 0.0;
 for (i = 0; i < population.size; i++){
  sum += population[i].adaptation;
  return sum / population.size;
 }
}
/*
def find_avg_adaptation(population)
	sum = 0
	population.each{|x| sum += x.adaptation}
	return sum/population.size.to_f 
end
*/

int find_best_individ(void){
int r = rand();
int i;
 for (i = 0; i < population.size; i++){
  if (r < population[i].normal_adapt){
   return i;
  }
 }
}
/* 
def find_best_individ()
	r = rand; 
	for i in 0...@population.size
		if r < @population[i].normal_adapt
			return i
		end
	end
end
*/
int crossing (first_number, second_number){
int first = [];
int second = [];
int i,t;
int k = rand();
int x = rand();
 for (i = 0; i < 8; i++ ){
  first << population[first_number].set[i]; // change
  second << population[second_number].set[i]; // change
 }
 if ( k < p_c ){
  t = rand() % 6 + 1;
  for (i = 0; t < first.size; i++){ 
   first[i],second[i] = first[i],second[i]; // change
  }
 }
 if (x < p_m){
  first[rand() % 8] = rand() % 8;
  second[rand() % 8] = rand() % 8;
 }
 new_population << individ.new(first); // change
 new_population[-1].adaptation = check(new_population[-1].set);
 new_population << individ.new(second);
 new_population[-1].adaptation = check(new_population[-1].set);
}
/*
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
*/
int copy_population(population, number){
	int ind = individ population[number].set; // change
	ind.adaptation = population[number].adaptation;
	ind.normal_adapt = population[number].normal_adapt;
	return individ;
}
/*
def copy_population(population,number)
	individ = Individ.new(population[number].set)
	individ.adaptation = population[number].adaptation
	individ.normal_adapt = population[number].normal_adapt
	return individ
end
*/

int print_board(problem){
int i,j;
 for (i = 0; i < problem.size; i++){
  printf(" ");
  for (j = 0; j < problem[i]; j++){
   printf ("  | ");
  }
  printf("Q");
  printf(" | ");
  for (j = 0; problem[i]+1 < problem.size; j++ ){
   prinf("  | ");
  }
  if (i != problem.size-1){
   printf(" ");
   printf("-----------------------------------");
  }else{
   printf(" ");
  }
 }
}
/*
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
*/
int genetic(void){
int i = 0, k = 0, t = 0, number = -1, avd_adaptation;
int stop = 0;
 create_population();
 for (i; i < n; i++){
  population[i].adaptation = check(population[i].set);
 }
 while (!stop){
  normalize_adaptation();
  //print_adaptation();
  avd_adaptation = find_average_adaptation(population);
  printf("%d", k);
  printf(" | Adaptation = ");
  printf("%d", avg_adaptation);
  printf("\n");
  for (t; t < n/2; t++){
   first_number = find_best_individ();
   while (first_number == (second_number == find_best_individ()));{}
   crossing(first_number, second_number);
  }
  for (i, i < new_population.size; i++){
   if(new_population[i].adaptation == 28){
    stop = 1;
    printf("Сошлось");
    printf("\n");
    number = i;
   }
  }
  population = [];
  for (i; i < new_population.size){
   population << copy_population(new_population, i);
  }
  new_population = [];
  k += 1;
 }
 printf("%d", k);
 print_adaptation(population);
}
/*
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
*/
int main(void){
genetic();
}

