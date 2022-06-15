Scale celsius = new("°C", 1, 0);
Scale fahrenheit = new("°F", 1.8, 32);
Scale kelvin = new("K", 1, 273.15);

Temperature tempKelvin = new(kelvin, 0);
Temperature tempCelsius = tempKelvin.ToScale(celsius);
Temperature tempFahrenheit = tempKelvin.ToScale(fahrenheit);

Console.WriteLine(tempCelsius);
Console.WriteLine(tempFahrenheit);
Console.WriteLine(tempKelvin);

/// <summary>A.</summary>
class Scale {
    public readonly string symbol;

    public readonly double a;

    public readonly double b;

    public Scale(string symbol, double a, double b)
        => (this.symbol, this.a, this.b) = (symbol, a, b);
}

class Temperature {
    readonly Scale scale;

    readonly double value;

    public Temperature(Scale scale, double value)
        => (this.scale, this.value) = (scale, value);

    public Temperature ToScale(Scale target) {
        double tempCelsius = (value - scale.b) / scale.a;
        double tempTarget = (tempCelsius * target.a) + target.b;
        return new(target, tempTarget);
    }

    public override string ToString()
        => String.Format("{0:0.0} {1}", value, scale.symbol);
}
