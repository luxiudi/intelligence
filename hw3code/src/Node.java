import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;


public class Node {
	
	public HashMap<Node, Weight> children = null;
	public HashMap<Node, Weight> parents = null;
	public double activation = 0;
	public double err = 0;
	public double delta = 0;
	
	
	public Node(){
		children = new HashMap<Node, Weight>();
		parents = new HashMap<Node, Weight>();
	}

	public void AddOutConnection(Node n, Weight w){
		children.put(n, w);
	}
	
	public void RemoveOutConnection(Node n){
		children.remove(n);
	}
	
	public void AddInConnection(Node n, Weight w){
		parents.put(n, w);
	}
	
	public void RemoveinConnection(Node n){
		parents.remove(n);
	}
	//public void 
	
	private double sigmod(double x){
		
		double temp = Math.exp(-x);
		
		return 1.0/(1.0 + temp);
	}
	
	
	/**
	 * Checks each individual input node, if they are activated, take the value of their weights
	 * and add it to the total input level.
	 * 
	 * If the total passes our activation threshold, set activated to true
	 * @return
	 */
	public void UpdateActivation(){
				
		Iterator<Entry<Node, Weight>> i = parents.entrySet().iterator();
		double inputLevels = 0;
		while(i.hasNext()){
			
			Entry<Node, Weight> ent  = i.next();
			Node n = ent.getKey();
			Weight w = ent.getValue();
			
			inputLevels += n.activation * w.weight;
		}
		this.activation = sigmod(inputLevels);
	}
	
	public void UpdateWeights(){
		
		updateError();
		
		Iterator<Entry<Node, Weight>> i = parents.entrySet().iterator();
		double temp = 0;
		while(i.hasNext()){
			
			Entry<Node, Weight> ent  = i.next();
			Weight w = ent.getValue();
			
			w.weight = w.weight + NeuralNetwork.alpha*delta;
		}
		this.err = temp;
	}
	
	private void updateError(){
		
		Iterator<Entry<Node, Weight>> i = children.entrySet().iterator();
		double temp = 0;
		while(i.hasNext()){
			
			Entry<Node, Weight> ent  = i.next();
			Node n = ent.getKey();
			Weight w = ent.getValue();
			
			temp += n.delta*w.weight;
		}
		
		this.err = temp;
		this.delta = temp*activation*(1-activation);
		
	}
}
