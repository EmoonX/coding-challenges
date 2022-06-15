Celsius celsius = new(14);
Console.WriteLine(celsius);

class Temperature {
    protected double value;

    public Temperature(double value)
        => this.value = value;
}

class Celsius : Temperature {
    public Celsius(double value) : base(value) {}

    public override string ToString()
        => String.Format("{0} °C", value);
}
