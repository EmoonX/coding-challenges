Scale celsius = new("°C", 1, 0);
Scale fahrenheit = new("°F", 1.8, 32);
Scale kelvin = new("K", 1, 273.15);

Temperature tempKelvin = new(kelvin, 0);
Temperature tempCelsius = tempKelvin.ToScale(celsius);
Temperature tempFahrenheit = tempKelvin.ToScale(fahrenheit);

Console.WriteLine(tempCelsius);
Console.WriteLine(tempFahrenheit);
Console.WriteLine(tempKelvin);

/// <summary>A temperature scale.</summary>
class Scale {

    /// <summary>Symbol to be printed as measurement unit.</summary>
    public readonly string symbol;

    /// <summary>Angular coefficient.</summary>
    public readonly double a;

    /// <summary>Linear coefficient.</summary>
    public readonly double b;

    /// <summary>Initializes scale.</summary>
    public Scale(string symbol, double a, double b)
        => (this.symbol, this.a, this.b) = (symbol, a, b);
}

/// <summary>Represents a temperature in given scale and degrees.</summary>
class Temperature {

    /// <summary>Scale temperature is in.</summary>
    readonly Scale scale;

    /// <summary>How many degrees.</summary>
    readonly double degrees;

    /// <summary>Initializes temperature.</summary>
    public Temperature(Scale scale, double degrees)
        => (this.scale, this.degrees) = (scale, degrees);

    /// <summary>Converts temperature to target scale.</summary>
    public Temperature ToScale(Scale target) {
        double tempCelsius = (degrees - scale.b) / scale.a;
        double tempTarget = (tempCelsius * target.a) + target.b;
        return new(target, tempTarget);
    }

    /// <summary>String representation with unit symbol.</summary>
    public override string ToString()
        => String.Format("{0:0.0} {1}", degrees, scale.symbol);
}
