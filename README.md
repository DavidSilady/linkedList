# mip-ut-14-sitarcik-par-ValiantGinger-4
mip-ut-14-sitarcik-par-ValiantGinger-4 created by GitHub Classroom

Author: David Silady

Purpose: Simulate a simple car dealership database

Functions:

"n" -> open a text file named "car_list.txt" from the working directory and load entries from it to the database

"v" -> print all the entries to the screen

"p" -> add one entry to the database:
		
Followed by the position of the new entry:
		
			"[position in the database]"
		
Followed by information about the car:

			"[type]"
			"[manufacturer]"
			"[location]"
			"[price]"
			"[production year]"
			"[condition]"
			
"z" -> delete all the cars with manufacturer name containing the entered line (not case sensitive):

Followed by:

			"[part of the manufacturer name for deletion]"
			
"h" -> find and print all the cars with the entered manufacturer name:

Followed by:

			"[wanted manufacturer name]"
			
"a" -> updates the price of all the cars with the entered manufacturer name and older than entered year

Followed by:

			"[wanted manufacturer name]"
			"[production year]"
			
"k" -> end
