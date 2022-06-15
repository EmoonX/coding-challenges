Celsius celsius = new(-40);
Fahrenheit fahrenheit = celsius.ToFahrenheit();
Kelvin kelvin = celsius.ToKelvin();
Console.WriteLine(celsius);
Console.WriteLine(fahrenheit);
Console.WriteLine(kelvin);

class Temperature {
    protected double value;

    protected Temperature(double value)
        => this.value = value;
}

class Celsius : Temperature {
    public Celsius(double value) : base(value) {}

    public Fahrenheit ToFahrenheit() {
        double value = (this.value * 1.8) + 32;
        return new(value);
    }

    public Kelvin ToKelvin() {
        double value = this.value + 273.15;
        return new(value);
    }

    public override string ToString()
        => String.Format("{0:.0} °C", value);
}

class Fahrenheit : Temperature {
    public Fahrenheit(double value) : base(value) {}

    public override string ToString()
        => String.Format("{0:.0} °F", value);
}

class Kelvin : Temperature {
    public Kelvin(double value) : base(value) {}

    public override string ToString()
        => String.Format("{0:.0} K", value);
}
