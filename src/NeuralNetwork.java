import java.util.ArrayList;
import java.util.Iterator;

public class NeuralNetwork {

	public ArrayList<InputNode> inputLayer = new ArrayList<InputNode>();
	public ArrayList<HiddenNode> hiddenLayer = new ArrayList<HiddenNode>();
	public ArrayList<OutputNode> outputLayer = new ArrayList<OutputNode>();

	private int numInputs;
	private int numHidden;
	private int numOutput;
	private boolean debug = false;
	public static double alpha = 0.15;

	public NeuralNetwork(int numInputs, int numHidden, int numOutput) {

		this.numHidden = numHidden;
		this.numInputs = numInputs;
		this.numOutput = numOutput;

		createNodes();
		setupConnections();
	}

	/**
	 * Forward propagation, traverse hidden layer to update their activation
	 * values based on inputs Traverse output layers to update their activation
	 * values based on hidden nodes
	 * 
	 * @param inputValues
	 *            used for inputting the activation values for the input nodes
	 */
	public double[] FeedForward(double[] inputValues) {

		for (int x = 0; x < inputValues.length; x++) {

			inputLayer.get(x).activation = inputValues[x];

		}

		for (int x = 0; x < hiddenLayer.size(); x++) {
			hiddenLayer.get(x).UpdateActivation();

		}

		for (int x = 0; x < outputLayer.size(); x++) {
			outputLayer.get(x).UpdateActivation();
			// System.out.println(outputLayer.get(x).activation);

		}

		return generateOutput();
	}

	/**
	 * Back propagate the differences between the outputnode values and actual
	 * values
	 * 
	 * @param correcOutputValues
	 */
	public void BackPropagte(double[] correcOutputValues) {

		for (int x = 0; x < outputLayer.size(); x++) {
			OutputNode on = outputLayer.get(x);
			on.err = correcOutputValues[x] - on.activation;
			// System.out.println(on.err);
			on.UpdateWeights1();
		}

		for (int x = 0; x < hiddenLayer.size(); x++) {

			HiddenNode hn = hiddenLayer.get(x);
			hn.UpdateWeights();

		}

		for (int x = 0; x < inputLayer.size(); x++) {
			InputNode in = inputLayer.get(x);
			in.UpdateWeights();
		}
	}

	private void setupConnections() {

		InputNode temp = new InputNode();
		temp.activation = -1;
		inputLayer.add(temp);
		numInputs++;

		// for each input, make a connection to a hidden node
		for (int x = 0; x < numInputs; x++) {
			InputNode in = inputLayer.get(x);

			for (int y = 0; y < numHidden; y++) {
				HiddenNode h = hiddenLayer.get(y);
				// makeConnection(in, h);
				Weight w = new Weight(randomWeight());
				// System.out.println("H WEIGHT " + w.weight);
				in.children.put(h, w);
				h.parents.put(in, w);

			}
		}

		HiddenNode htemp = new HiddenNode();
		htemp.activation = -1;
		hiddenLayer.add(htemp);
		numHidden++;

		for (int x = 0; x < numHidden; x++) {

			HiddenNode h = hiddenLayer.get(x);
			for (int y = 0; y < numOutput; y++) {
				OutputNode o = outputLayer.get(y);
				Weight w = new Weight(randomWeight());
				h.children.put(o, w);
				o.parents.put(h, w);
			}
		}

	}

	/**
	 * Makes an edge between two nodes. Puts a random weight into the edge
	 * 
	 * @param from
	 * @param to
	 */
	private void makeEdge(Node from, Node to) {
		double d;
		d = randomWeight();
		Weight w = new Weight(d);
		from.children.put(to, w);
		to.parents.put(from, w);
	}

	private void createNodes() {

		// make all input nodes
		for (int x = 0; x < numInputs; x++) {
			InputNode n = new InputNode();
			inputLayer.add(n);
		}

		// make all hidden nodes
		for (int x = 0; x < numHidden; x++) {
			HiddenNode n = new HiddenNode();
			hiddenLayer.add(n);
		}

		// make all output nodes
		for (int x = 0; x < numOutput; x++) {

			OutputNode n = new OutputNode();
			outputLayer.add(n);
		}

	}

	private double[] generateOutput() {

		double[] o = new double[outputLayer.size()];
		for (int x = 0; x < outputLayer.size(); x++) {
			o[x] = outputLayer.get(x).activation;
		}
		return o;
	}

	private double randomWeight() {
		double n = 0;

		n = Math.random() - 0.5;

		return n/5.0;
	}

	public void printWeights() {

		for (int x = 0; x < numInputs; x++) {
			
			InputNode i = inputLayer.get(x);
			//System.out.println(i.);
			
		}

		for (int x = 0; x < numHidden; x++) {
			HiddenNode h = hiddenLayer.get(x);
		}

		for (int x = 0; x < numOutput; x++) {
			OutputNode o = outputLayer.get(x);
		}

	}

}