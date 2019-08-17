/** Testing class for Hash Table**/

import java.io.*;
import java.util.*;

public class HashMainTest extends HashTableImp{
	
	public HashMainTest(int size){
		super(size);
	}
	
	public static void main(String []args){
		HashMainTest hashMain;
		int tableSize;
		String str;
		String fileName;
		
		if(args.length==2){
			tableSize = Integer.valueOf(args[0]); //getting hashtable size from command line arguements
			hashMain = new HashMainTest(tableSize);
			fileName = args[1]; //get the fileName
			
			try{
				BufferedReader buffer = new BufferedReader(new FileReader(fileName));
				while((str=buffer.readLine())!=null){
					String s = str.replaceAll("\\W"," ");//replace alphanumeric characters from whitespaces
					String split[] = s.split("\\s+");//split lines
					
					for(String string:split){
						hashMain.insert(string);// insert strings into hash table
					}
					
				}
				
			}catch(Exception e){
				System.out.println(e);	
				System.exit(0);
			}
			hashMain.getBucketSize(tableSize);//display no of elements in each bucket
			
			Scanner sc = new Scanner(System.in);
			String strKey;
			
			//searching for elements in hashTable
			do{
				System.out.println("\nEnter a key string: ");
				strKey = sc.nextLine();
				System.out.println("Value = "+hashMain.search(strKey));
			}while(!strKey.equals("exit"));
			
			
		}else{
			System.out.println("Argument be like==> java HashMainTest <no_of_buckets> <samlpe_file_name> "); //printing message for wrong arguments
		}
		
	}	
}

