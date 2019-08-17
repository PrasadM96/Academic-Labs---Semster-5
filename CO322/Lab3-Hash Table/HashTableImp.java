/*********************************************
 * CO322: Data structures and algorithms
 * Implementation of the hashTable
 *********************************************/
 
class HashTableImp implements HashTable {

	private int n;//to count the no of key/value pairs
	
    private static class Node {
      String key;
      int value=0;
      Node next;  //pointer to next node in the list;
    }
 
 	public Node[] hashTable;//hash table
 
    public HashTableImp(int buckets) {
		hashTable = new Node[buckets];//create the hashTable
    }


	/** function for inserting the key/value pair**/
	public void insert(String key){
		int bucketNo =hashfunc(key);//get the bucket index from hashfunction
		Node newNode = null; 
		
		try{
			newNode = hashTable[bucketNo]; //get reference to the correspoding node
			
			//go through the list to check whether key exists or not
			while(newNode!=null){ 
				if(newNode.key.equals(key)){
					break;
				}
				newNode = newNode.next;
			}
				
			if(newNode !=null){
				newNode.value++; //if key exists increment the value 
			}else{
			    //if not create new node and add to end of the list of the bucket
				Node newNode1 = new Node();  
				newNode1.key = key;
				newNode1.value++;                                          
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
				newNode1.next = hashTable[bucketNo];
				hashTable[bucketNo] = newNode1;
				n++;
			}
			
		}catch(Exception e){
			System.out.println(e);
		}
		
		
		
	}
	/** function for searching the value **/
	public int search(String key){
		int bucketNo = hashfunc(key);//get the bucket number
		Node newNode = hashTable[bucketNo];//get the list to a node
		
		//go through list and check for the key
		while(newNode!=null){
			if(newNode.key.equals(key)){
				return newNode.value;
			}
			newNode = newNode.next;
		}
		
		return 0;//key not found
	} 
	 
	
	
	/**hash function**/
	public int hashfunc(String key){
		int val=0;
		int mul=71;
		//sum up the ascci value of the word
		for(int i=0;i<key.length();i++){
			val=(val*mul+key.charAt(i))%hashTable.length;
		}
		
		return val%hashTable.length;//return modulus of sum of ascii values
	}  
	
	/**display each bucket size, minimumand maximum no of entries, average and standard deviation**/
	public void getBucketSize(int size){
		int m=0,max=0,min=100000;
		float dev=0;
		float average =(float) n/size;
		
		
		for(int i=0;i<size;i++){
			Node newNode = hashTable[i];
			while(newNode != null){
				m++;
				newNode = newNode.next;
			}
			if(max<m){max=m;}//find maximum no of entries
			if(min>m){min=m;}//find minimum no of entries
			System.out.println("Bucket "+(i+1)+" -- no of elements => "+m); //display no of entries in the bucket
			dev += Math.pow((m-average),2);
			m=0;
		}
		
		System.out.println("The minimum no of entries => "+min+"\nThe maximum no of entries => "+max);
		
		double deviation = Math.sqrt(dev/size);//calculate standard deviation
		
		System.out.println("Total elements => "+getHashTableSize()); //total no of entries in hash table
		System.out.println("Average no of elements per bucket => "+average);//average no of entries in a bucket
		System.out.println("Standard deviation => "+deviation);//display the standard deviation
		
	}
	
	/**function to check the key/value exists**/
	public boolean isContain(String key){
		int bucketNo = hashfunc(key);//get bucket number
		Node newNode = hashTable[bucketNo]; //get corresponding list
		
		//go through list and check for the key
		while(newNode!=null){
			if(newNode.key.equals(key)){
				return true;
			}
			newNode = newNode.next;
		}
		
		return false;//key not found
	}
	
	/** function to get the hash table size**/
	public int getHashTableSize(){
		return n;
	}
	  

}// end HashTableImp 
