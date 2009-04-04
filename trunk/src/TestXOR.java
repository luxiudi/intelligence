
public class TestXOR {
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		NeuralNetwork nn = new NeuralNetwork(2, 3, 1);
		
		double[] in1 = {1,1};
		double[] in2 = {1,0};
		double[] in3 = {0,1};
		double[] in4 = {0,0};
		
		double[] o1 = {-1};
		double[] o2 = {1};
		double[] o3 = {1};
		double[] o4 = {-1};
		
		
		
		
		for(int x = 0; x<10; x++){
	
			nn.FeedForward(in1);
			nn.BackPropagte(o1);
			
			nn.FeedForward(in2);
			nn.BackPropagte(o2);
			
			nn.FeedForward(in3);
			nn.BackPropagte(o3);
			
			nn.FeedForward(in4);
			nn.BackPropagte(o4);

			
		}
	
		double output[] = nn.FeedForward(in3);
		System.out.println(output[0]);
	
	}

}
