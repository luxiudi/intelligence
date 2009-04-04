public class Classifier {

	private static int trainingsize = 10000;
	private static int testsize = 1000;
	private static int hiddensize = 75;
	private static double learning = 0.2;
	private static double numEpoch = 30;

	private static int testSuccess = 0;
	private static int trainSuccess = 0;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		ImageData[] images = null;
		ImageData[] tests = null;

		if (args.length != 0) {

			hiddensize = Integer.parseInt(args[0]);
			learning = Double.parseDouble(args[1]);
			numEpoch = Integer.parseInt(args[2]);
		}

		try {
			images = ImageParser.ReadFile(trainingsize, "training-10k.txt");
			tests = ImageParser.ReadFile(testsize, "test-1k.txt");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		
		
		NeuralNetwork nn = new NeuralNetwork(14 * 14, hiddensize, 10);
		nn.alpha = learning;
		for (int z = 0; z < numEpoch; z++) {
			System.out.println("EPOCH " + (z + 1));

			runFB(images, nn);

		}
		runTrainingTest(images, nn);
		runTest(tests, nn);

		System.out.println("test " + testSuccess);
		System.out.println("training " + trainSuccess);

	}

	private static void runTrainingTest(ImageData[] images, NeuralNetwork nn) {

		int correct = 0;

		double input[] = new double[14 * 14];
		for (int x = 0; x < trainingsize; x++) {
			int count = 0;
			for (int a = 0; a < 14; a++)
				for (int b = 0; b < 14; b++) {
					input[count] = images[x].pixelValues[a][b];
					// System.out.println(input[count]);
					// if ((double) images[x].pixelValues[a][b] / 255.0 > 0)
					// input[count] = 1;
					// else
					// input[count] = 0;

					// System.out.println(input[count]);
					count++;
				}
			double output[] = nn.FeedForward(input);

			int max = 0;
			double te = 0;
			for (int t = 0; t < output.length; t++) {
				if (te <= output[t]) {
					max = t;
					te = output[t];
				}
			}

			// System.out.println("@@@@@@@@@@@@@@@@@ " + max + "  " +
			// images[x].label);
			// System.out.println();

			System.out.print(images[x].label + " ");
			printArray(output);

			if (max == images[x].label)
				correct++;
		}
		trainSuccess = correct;
		System.out.println(correct);

	}

	private static void runTest(ImageData[] images, NeuralNetwork nn) {

		int correct = 0;

		double input[] = new double[14 * 14];
		for (int x = 0; x < testsize; x++) {
			int count = 0;
			for (int a = 0; a < 14; a++)
				for (int b = 0; b < 14; b++) {
					input[count] = images[x].pixelValues[a][b];
					// System.out.println(input[count]);
					// if ((double) images[x].pixelValues[a][b] / 255.0 > 0)
					// input[count] = 1;
					// else
					// input[count] = 0;

					// System.out.println(input[count]);
					count++;
				}
			double output[] = nn.FeedForward(input);

			int max = 0;
			double te = 0;
			for (int t = 0; t < output.length; t++) {
				if (te <= output[t]) {
					max = t;
					te = output[t];
				}
			}

			// System.out.println("@@@@@@@@@@@@@@@@@ " + max + "  " +
			// images[x].label);
			// System.out.println();

			System.out.print(images[x].label + " ");
			printArray(output);

			if (max == images[x].label)
				correct++;
		}
		testSuccess = correct;
		System.out.println(correct);

	}

	private static void runFB(ImageData[] images, NeuralNetwork nn) {

		double input[] = new double[14 * 14];

		for (int x = 0; x < trainingsize; x++) {
			int count = 0;
			for (int a = 0; a < 14; a++)
				for (int b = 0; b < 14; b++) {
					input[count] = images[x].pixelValues[a][b];
					// System.out.println(input[count]);
					// if ((double) images[x].pixelValues[a][b] / 255.0 > 0)
					// input[count] = 1;
					// else
					// input[count] = 0;

					// System.out.println(input[count]);
					count++;
				}
			double trueOutput[] = new double[10];
			double output[] = nn.FeedForward(input);

			int max = 0;
			double te = 0;
			for (int t = 0; t < output.length; t++) {
				if (te <= output[t]) {
					max = t;
					te = output[t];
				}
			}
			//
			// System.out.println("@@@@@@@@@@@@@@@@@ " + max + "  " +
			// images[x].label);
			// // System.out.println();

			for (int t = 0; t < trueOutput.length; t++) {
				trueOutput[t] = 0;
			}
			trueOutput[images[x].label] = 1;

			nn.BackPropagte(trueOutput);

		}
	}

	private static void printArray(double[] d) {

		// System.out.println("new instance");
		for (int x = 0; x < d.length; x++) {

			System.out.printf("%5.4f ", d[x]);
			// System.out.print(d[x]%5.3 + " ");
		}
		System.out.println();
	}

}
