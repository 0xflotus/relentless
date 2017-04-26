public class Entry {

	private float price;
	private String title;

	public Entry(float price, String title) {
		super();
		this.price = price;
		this.title = title;
	}

	public float getPrice() {
		return price;
	}

	public String getTitle() {
		return title;
	}

	@Override
	public String toString() {
		return this.getTitle() + ": " + this.getPrice() + " Euro";
	}
}