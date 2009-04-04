
public class test {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		method();
		
	}

	public static void method(){
		
		class value{
			 public int num = 0;
		 }
		
		 class holder{
				
				public value v;
				public holder(){
					
				}
		 }

		holder h1 = new holder();
		 
		holder h = new holder();
		
		value v = new value();
		v.num = 10;
		
		
		
		h1.v = v;
		h.v = v;
		
		
		System.out.println(h1.v.num);
		System.out.println(h.v.num);
		
		h1.v.num = 20;
		
		System.out.println(h1.v.num);
		System.out.println(h.v.num);
		
	}
	

	
	
}
