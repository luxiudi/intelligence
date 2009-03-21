import java.util.Iterator;
import java.util.Map.Entry;


public class OutputNode extends Node{

	public OutputNode(){
		
		super();
	}

	
	/**
	 * UpdateWeights for OutputNodes. Overwritten method, since updates are different for OuptNodes
	 * 
	 * Iterate through all parent (hidden) nodes, and update the edges with new weights
	 */
	public void UpdateWeights(){
		
		delta = activation*(1-activation)*err;
		
		Iterator<Entry<Node, Weight>> i = parents.entrySet().iterator();
		while(i.hasNext()){
			
			Entry<Node, Weight> ent  = i.next();
			Node n = ent.getKey();
			Weight w = ent.getValue();
			
			w.weight = w.weight + NeuralNetwork.alpha*delta;
		}		
	}

	
}
