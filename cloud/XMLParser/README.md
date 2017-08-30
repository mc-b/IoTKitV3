## ![IDevice Icon](../../base/images/icon_glossary.gif) XML (Extensible Markup Language)


```xml
<a>
    <b>
	    <c>
		    <d c="123">eins</d>
		    <e>zwei</e>
		    <f>drei</f>
	    </c>
    </b>
</a>
```

Beispiel XML Code 

- - -

```xml
SP_XmlDocument a
    SP_XmlElementNode b
        SP_XmlElementNode c
            SP_XmlElementNode d c=123
                SP_XmlCDataNode eins
            SP_XmlElementNode e 
                SP_XmlCDataNode zwei
            SP_XmlElementNode f
                SP_XmlCDataNode drei               
```

Abbildung XML Code im Speicher

- - -

Die [Extensible Markup Language (engl. „erweiterbare Auszeichnungssprache“)](http://de.wikipedia.org/wiki/Extensible_Markup_Language), abgekürzt XML, ist eine Auszeichnungssprache zur Darstellung hierarchisch strukturierter Daten in Form von Textdateien. XML wird u. a. für den plattform- und implementationsunabhängigen Austausch von Daten zwischen Computersystemen eingesetzt, insbesondere über das Internet.

Mittels der [spxml (Simple Plain Xml parser)](http://developer.mbed.org/users/hlipka/code/spxml/) Library können XML Strukturen geparst und anschliessend traversiert werden.

### Links

*  [mbed OS V2 Variante](https://developer.mbed.org/compiler/#import:/teams/smdiotkit2ch/code/XMLParser/)
