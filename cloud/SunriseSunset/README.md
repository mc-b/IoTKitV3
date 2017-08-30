## Sunset Sunrise (JSON)

![](../../images/SunriseSunset.png)

- - -

Sunrise Sunset stellt ein API zur Verfügung, mittels dem die Sonnen Auf- und Untergangszeiten für einen bestimmten Ort abgefragt werden können.

**Links**

*   [Website](http://sunrise-sunset.org/)
*   [API Beschreibung](http://sunrise-sunset.org/api)
*   [Sonnen Auf- und Untergang für Zürich](http://sunrise-sunset.org/search?location=Z%C3%BCrich%2C+Schweiz)

### Beispiel: Abfrage für Zürich 

[http://api.sunrise-sunset.org/json?lat=47.3686498&amp;lng=8.5391825](http://api.sunrise-sunset.org/json?lat=47.3686498&lng=8.5391825)

```js
{"results":
   { "sunrise":"5:38:12 AM",
     "sunset":"5:31:12 PM",
     "solar_noon":"11:34:42 AM",
     "day_length":"11:53:00",
     "civil_twilight_begin":"5:07:47 AM",
     "civil_twilight_end":"6:01:38 PM",
     "nautical_twilight_begin":"4:32:04 AM",
     "nautical_twilight_end":"6:37:21 PM",
     "astronomical_twilight_begin":"3:55:32 AM",
     "astronomical_twilight_end":"7:13:52 PM"
   },
   "status":"OK"}
```


### Links

*  [mbed OS V2 Variante](https://developer.mbed.org/compiler/#import:/teams/smdiotkit2ch/code/SunriseSunset/)
