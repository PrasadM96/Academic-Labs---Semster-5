class Train {
    static int [][] cost = {{0, 3, 12, 23, 41}, // cost from 0
                  			{0, 0,  2,  4, 34}, // cost from 1
                  			{0, 0,  0,  12, 3}, // cost from 2
                  			{0, 0,  0,  0, 12}, // cost from 3
                  			{0, 0,  0,  0,  0}  // cost from 4
                      };

    static int iMax = 5;

    // Just for testing, min cost from 0 to 4 should be 8.
    static int answer = 8;

    public static int minCost(int i, int j) {
		
        int dis[] = new int[j-i+1]; //create an array to store the distances
       
	   for (int k=0; k<=j-i; k++){
           dis[k] = Integer.MAX_VALUE; // setting all elements of the array to integer maximum value
		}
           dis[0] = 0;

        //checking for minimum distance
        for (int k=i; k<=j; k++){
           for (int m=k+1; m<=j; m++){
              if (dis[m-i] > dis[k-i] + cost[k][m]){
                 dis[m-i] = dis[k-i] + cost[k][m];
			  }
		   }
		}
        return dis[j-i];

	}

    public static void main(String [] args) {
    	int r = minCost(0,4); 

    	if(r == answer)
    	    System.out.println("Your implementation might be correct");
    	else
    	    System.out.println("Too bad. Try again (" + r + ")");
        }
}
