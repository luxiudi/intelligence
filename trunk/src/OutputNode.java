import java.util.Iterator;
import java.util.Map.Entry;


public class OutputNode extends Node{

	public OutputNode(){
		
		super();
		this.name = "output";
	}

	
	/**
	 * UpdateWeights for OutputNodes. Overwritten method, since updates are different for OuptNodes
	 * 
	 * Iterate through all parent (hidden) nodes, and update the edges with new weights
	 */
	public void UpdateWeights1(){
		
		delta = activation*(1.0-activation)*err;
		//System.out.println("ACI" + this.activation);
		//System.out.println("delta" + delta);
		//delta = 0.73;
		
		
		Iterator<Entry<Node, Weight>> i = parents.entrySet().iterator();
		while(i.hasNext()){
			
			Entry<Node, Weight> ent  = i.next();
			Node k = ent.getKey();
			
			Weight w = ent.getValue();
			
			//System.out.println("h2 " + ent.getValue().weight);
			
			//System.out.println("OUTPUT W " + w.weight + "activation " + k.activation);
			w.weight = w.weight + NeuralNetwork.alpha*delta*k.activation;
//			if(ww != w.weight)
//				System.out.println("DIFFERENT@@@@@@@@@@@@@@@@@@@@@@@@@");
//			
			//System.out.println("h1 " + ent.getValue().weight);
			
//			System.out.println("OP AF W: " + w.weight);
		}		
	}

	
}
