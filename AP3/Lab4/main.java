public static void main(String args[]) throws InterruptedException {
		(new CorrectorThread()).start();
		message = "Mares do not eat oats.";
		Thread.sleep(2000);
		//Key statement 2:
		System.out.println(message);
	}
}