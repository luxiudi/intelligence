import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;


public class Node {
	
	public HashMap<Node, Weight> outbound = null;
	public HashMap<Node, Weight> inbound = null;
	public double activation = 0;
	public double value = 0;
	public boolean activated = false;
	
	
	public Node(){
		outbound = new HashMap<Node, Weight>();
	}

	public void AddOutConnection(Node n, Weight w){
		outbound.put(n, w);
	}
	
	public void RemoveOutConnection(Node n){
		outbound.remove(n);
	}
	
	public void AddInConnection(Node n, Weight w){
		inbound.put(n, w);
	}
	
	public void RemoveinConnection(Node n){
		inbound.remove(n);
	}
	//public void 
	
	/**
	 * Checks each individual input node, if they are activated, take the value of their weights
	 * and add it to the total input level.
	 * 
	 * If the total passes our activation threshold, set activated to true
	 * @return
	 */
	public boolean CheckActivation(){
				
		Iterator<Entry<Node, Weight>> i = inbound.entrySet().iterator();
		double inputLevels = 0;
		while(i.hasNext()){
			
			Entry<Node, Weight> ent  = i.next();
			Node n = ent.getKey();
			Weight w = ent.getValue();
			
			if(n.activated){
				inputLevels += n.value * w.w;
			}	
		}
		
		if(inputLevels > this.activation){
			activated = true;
		}else
			activated = false;
		
		return activated;
		
	}
}
