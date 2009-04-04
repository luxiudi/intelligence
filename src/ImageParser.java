import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.StringTokenizer;

public class ImageParser {
	
	private static int numImages = 10000;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			ReadFile(10000,"training-10k.txt");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.out.println("ERROR READING FILE");
		}
		System.out.println();

	}

	public static ImageData[] ReadFile(int size, String fileName) throws Exception {

		//File f = new File("training-10k.txt");
		File f = new File(fileName);
		
		ImageData[] images = new ImageData[size];
		System.out.println(f.length());

		FileReader fr = new FileReader(f);
		BufferedReader br = new BufferedReader(fr);

		for (int y = 0; y < size; y++) {
			
			
			String s = br.readLine();
			s = s.substring(1, 2);
			//System.out.println(s + " " + y);
			images[y] = new ImageData();
			images[y].label = Integer.parseInt(s);
			
			
			int count = 0;
			for (int row = 0; row < 14; row++) {
				s = br.readLine();

				//System.out.println(s);
				
				StringTokenizer st = new StringTokenizer(s, " ");
				int column = 0;
				while (st.hasMoreTokens()) {
					
					String value = st.nextToken();
					images[y].pixelValues[row][column] = Double.parseDouble(value)/255.0;
					
					//System.out.println(st.nextToken());
					column++;
				}
				
			}

		}

//		
//		for(int x = 0; x<numImages; x++){
//			
//			
//			int[][] array = images[x].pixelValues;
//			
//			for(int a=0; a<14; a++){
//				for(int b = 0; b<14; b++){
//					
//					int value = array[a][b];
//					String space = "";
//					if(value<10)
//						space = space + "   ";
//					else if( value<100){
//						space = space + "  ";
//					}else{
//						space = space + " ";
//					}
//						
//					System.out.print(array[a][b]+ space);
//				}
//				System.out.println();
//			}
//			System.out.println();
//		}
		
		

		return images;

	}

}