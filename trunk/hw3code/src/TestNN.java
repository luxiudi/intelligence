
public class TestNN {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		NeuralNetwork nn = new NeuralNetwork(3, 2, 1);
		
		
		InputNode i1 = nn.inputLayer.get(0);
		InputNode i2 = nn.inputLayer.get(1);
		InputNode i3 = nn.inputLayer.get(2);
		
		HiddenNode h4 = nn.hiddenLayer.get(0);
		HiddenNode h5 = nn.hiddenLayer.get(1);
		
		OutputNode o6 = nn.outputLayer.get(0);
		
		i1.children.clear();
		i2.children.clear();
		i3.children.clear();
		
		i1.parents.clear();
		i2.parents.clear();
		i3.parents.clear();
		
		h4.children.clear();
		h4.parents.clear();
		h5.children.clear();
		h5.parents.clear();
		
		o6.children.clear();
		o6.parents.clear();
		
		i1.activation =1;
		i2.activation = 1;
		i3.activation = 0;
		
		Weight w14 = new Weight(0.13);
		Weight w15 = new Weight(-0.2);
		
		Weight w24 = new Weight(0.06);
		Weight w25 = new Weight(-0.1);

		Weight w34 = new Weight(0.2);
		Weight w35 = new Weight(0.07);
		
		Weight w46 = new Weight(0.15);
		Weight w56 = new Weight(-0.01);
		
		i1.children.put(h4, w14);
		i1.children.put(h5, w15);
		
		i2.children.put(h4, w24);
		i2.children.put(h5, w25);
		
		i3.children.put(h4, w34);
		i3.children.put(h5, w35);
		
		h4.parents.put(i1, w14);
		h4.parents.put(i2, w24);
		h4.parents.put(i3, w34);
		
		h5.parents.put(i1, w15);
		h5.parents.put(i2, w25);
		h5.parents.put(i3, w35);
		
		h4.children.put(o6, w46);
		h5.children.put(o6, w56);
		
		o6.parents.put(h4, w46);
		o6.parents.put(h5, w56);
		
		double [] input = {1,1,0};
		double[] output = nn.FeedForward(input);
		
		System.out.println(i1.activation);
		System.out.println(i2.activation);
		System.out.println(i3.activation);
		System.out.println(h4.activation);
		System.out.println(h5.activation);
		System.out.println(o6.activation);
		
		
		
		System.out.println();
		double[] input1 = {1};
		nn.BackPropagte(input1);
		System.out.println("i1: " +i1.children.get(h4).weight);
		System.out.println("i2: " +i2.delta);
		System.out.println("i3: " +i3.delta);
		System.out.println();
		
		System.out.println("h4 weight: " +h4.children.get(o6).weight);
		System.out.println("h4 delta: " +h4.delta);
		System.out.println("h5 delta: " +h5.delta);
		System.out.println("h5 err: " +h5.err);
		System.out.println("h5 weight: " +h5.children.get(o6).weight);
		
		System.out.println();
		System.out.println("o6 delta  : " +o6.delta);
		System.out.println("e6: " +o6.err);
		System.out.println("w6: " +o6.parents.get(h4).weight);
		
		
		printArray(output);
		
		//System.out.println(Math.random());
		
	}
	private static void printArray(double[] d) {

		for (int x = 0; x < d.length; x++) {

			System.out.print(d[x] + " ");
		}
		System.out.println();
	}


}
