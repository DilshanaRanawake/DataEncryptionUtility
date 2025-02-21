## Data Encryption Utility
The utility is a simple command-line encryption and decryption tool that reads data from an input file, encrypts it using a given encryption key, and writes the encrypted data to an output file. Similarly, it can also read encrypted data from an input file, decrypt it using the same encryption key, and write the decrypted data to a decrypted file
<br /><br />
-> Command-Line Options:
	Format:
		[CFileName] [encrypt/decrypt] [input_file] [output_file] [encryption_key]

<br /><br />
--> In Windows<br />
For encryption:
 
		encryption_utility encrypt input.txt output.txt mykey
  
For decryption:
 
		encryption_utility decrypt output.txt decrypted.txt mykey
<br /><br />
--> In Linux<br />
For encryption:
		
  		./encryption_utility encrypt input.txt output.txt mykey
		
For decryption:
	
 		./encryption_utility decrypt output.txt decrypted.txt mykey

