# mip-ut-14-sitarcik-par-ValiantGinger-4
mip-ut-14-sitarcik-par-ValiantGinger-4 created by GitHub Classroom

Author: David Silady

Purpose: Simulate a simple car dealership database with basic functions

Each entry includes information:

		1. Type of vehicle
		2. Manufacturer
		3. Seller (location)
		4. Price
		5. Year of production
		6. Condition of the vehicle


Functions:

"o" -> open a text file named "car_list.txt" from the working directory and load entries from it to the database

"p" -> print all the entries to the screen

"a" -> add one entry to the database
		
Followed by the position of the new entry:
		
			"[position in the database]"
		
Followed by information about the car:

			"[type]"
			"[manufacturer]"
			"[seller location]"
			"[price]"
			"[production year]"
			"[condition]"
			
"d" -> delete all the cars with manufacturer name containing the entered line (not case sensitive)

Followed by:

			"[part of the manufacturer name for deletion]"
			
"f" -> find and print all the cars with the entered manufacturer name (not case sensitive)

Followed by:

			"[wanted manufacturer name]"
			
"u" -> updates the price of all the cars with the entered manufacturer name and older than entered year (not case sensitive)

Followed by:

			"[wanted manufacturer name]"
			"[production year]"
			
"k" -> end
