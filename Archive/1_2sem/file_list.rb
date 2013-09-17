=begin
if ARGV[0].to_i != 0
    Dir.foreach("#{Dir.pwd}") {|file_name|
   if IO.read("#{file_name}").size > 0 &&
      IO.read("#{file_name}").size >= ARGV[0].to_i
     puts "#{file_name}\n";
   end
   }
else
   Dir.foreach("#{Dir.pwd}") {|f_name| puts "#{f_name}\n"}
end
=end

f_list = Dir.entries("#{Dir.pwd}")
f_list.delete(".")
f_list.delete("..")
for i in 0...f_list.size
  puts "#{f_list[i]}" if IO.read(f_list[i]).size >= ARGV[0].to_i
end
