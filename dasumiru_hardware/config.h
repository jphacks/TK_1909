// WiFi Setting
const char* ssid = "yubenekoiPhone";
const char* password = "yubeshiumai";

// AWS IoT Setting
const char *awsEndpoint = "a1gzpf0os13m3l-ats.iot.us-east-2.amazonaws.com";
const int awsPort = 8883;
const char* pubTopic = "dasumiru";
const char* rootCA = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
"rqXRfboQnoZsG4q5WTP468SQvvG5\n" \
"-----END CERTIFICATE-----\n";

const char* certificate = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDWjCCAkKgAwIBAgIVAIqMUZVIIUg4VuJ8YyFuRQSP5aETMA0GCSqGSIb3DQEB\n" \
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n" \
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xOTEwMjYwNjQ3\n" \
"MzJaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n" \
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDMSSBJAZZR5DTEANyP\n" \
"HHfNl7glCyx1JX3JxWpCiDkiEuhvEVUhMw3udRNs3aqY2BAiIJfhFMWIaU9OpJfo\n" \
"q4tatzN9WcRrb2H+G/cAWuNktt0SsHixqCR8MENN9Q6mn40f8p0+4bgpN08MwqTW\n" \
"myuj/5g3i9kAhs6LjzW7xkhe1EQoU70887YoUHJtkLDlhOWE7p8+iqTda7d8Y3pL\n" \
"0hyfSau7XkqbjPIIQLzMvdbKMsY+fxY1gm/rgmu0RxdE0lZBR8N4u9CQwIhTiiHQ\n" \
"LcZR1yLRfruqPRiLO2ekHBuNDfhNSqcBHhRGgzYP2rk8b5HqrWp0NYDSrAstvaA8\n" \
"81kDAgMBAAGjYDBeMB8GA1UdIwQYMBaAFLPICEvxfQbcF4OmGe6gzhQ8DVHkMB0G\n" \
"A1UdDgQWBBS6dA1PWj3B1rh1XAvo6tIbQGtdojAMBgNVHRMBAf8EAjAAMA4GA1Ud\n" \
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAFoCyKg4I4VXoj66ir4+5NUQw\n" \
"b8iaAUKakAJ5+bP+FybfHljedKUSZJ8FUVBaVF/TapITweRR/2Kug2JozzDu+hFr\n" \
"ItiBAnbcaZhCzrAJ7y/RYD8YVQNMIesS27f3ijKI/nHmlBAqhtb1CwEJxNNrs2eM\n" \
"790R4ZPTzdFihYGupOGG+auIibNKS2474mYMw8cP/qJ7rjl0J0XJgPsjSg609161\n" \
"F9xVsA6Zna2sEv1QMsoNe59pgVAD/0h5YukRUd4IsyVdSIDf6k1dnYYDJ3j8139b\n" \
"0AMInGV2gOA9QUa5yO+JKupmlzRqSd8cOjalxGgLUOJ4WTlyp+DSPpaeFS3pkA==\n" \
"-----END CERTIFICATE-----\n" \
;

const char* privateKey = \
"-----BEGIN RSA PRIVATE KEY-----\n" \
"MIIEpQIBAAKCAQEAzEkgSQGWUeQ0xADcjxx3zZe4JQssdSV9ycVqQog5IhLobxFV\n" \
"ITMN7nUTbN2qmNgQIiCX4RTFiGlPTqSX6KuLWrczfVnEa29h/hv3AFrjZLbdErB4\n" \
"sagkfDBDTfUOpp+NH/KdPuG4KTdPDMKk1psro/+YN4vZAIbOi481u8ZIXtREKFO9\n" \
"PPO2KFBybZCw5YTlhO6fPoqk3Wu3fGN6S9Icn0mru15Km4zyCEC8zL3WyjLGPn8W\n" \
"NYJv64JrtEcXRNJWQUfDeLvQkMCIU4oh0C3GUdci0X67qj0YiztnpBwbjQ34TUqn\n" \
"AR4URoM2D9q5PG+R6q1qdDWA0qwLLb2gPPNZAwIDAQABAoIBAQCge+4mDF4n9UxS\n" \
"ko6yyt1/IOqkB1Qkr5BTG4ivvc6Mayg4YPhsvWv7YfQhuT5VFqAN/2bxhtzrnjeU\n" \
"g49nVKSEXpnPpt68u+LSuutfVwd+zn18OjCG+J25Bj1Jl/OriHpYl8Naa/6+Oloa\n" \
"nyraAUrWamwNbwrJ9B1828ONwWaHP3jkMS9T535s1tMkTY0C5DidLydAhtmd0DOz\n" \
"lP0MAFg5X5JTDunZdUHaeE6vidGbpTbpfWuaiftO3d1SsPPZZzqV3uIUztpjk+uZ\n" \
"19siCe7lDx7YsT/6sBq9potp/kEdBxC3iFtrXSpRGObIAawegL5WgslMGehmLomd\n" \
"vNQw3XGZAoGBAOptRJ3nDXzkZZwprCSoT6To3UAuEsLXG7SADOlyGCQCTe8/mrUd\n" \
"xwpWYOuS0upq3ImD0JYNG1v/gyHixH4w8K5Grl2/IKEJLIAepwTYBccNoucpVAVH\n" \
"/JUki/HqrNwOx75e+Q3CfGZWP2wW/A0duRwrHsGW8z7rzrwSNA1BswbXAoGBAN8V\n" \
"x1ltPsi5nvMRuTt7PdZKGGZo+Ftn2wFhdjiyPUJb77rHoCMAcfX08K7A/4w8N95U\n" \
"xvgM96nsM0IUJdi3deVkPSQhtkdjvwRTCsHyUYLp5YqiGug07xCETx7swWuKqhoD\n" \
"/iNv0yaSG5pupuRn4ZIee7YIFFXmaY3qpHChEzW1AoGAaomuHXTcFF5YL1hg+2fi\n" \
"ijeqFXja3eGUnbt0IsPPZM4HTSvCy3z08CXBdk4LvK1D/NsC+K6MOIsutT+xvQfQ\n" \
"2eMVa1VpJsZciv1jOjhSp9vypMuLe7rzd3RchVz5oii1bjcLSM2Sa4/W0vC/K9bO\n" \
"QZb3K1PGyFmyYpaDQWMSUZECgYEAm/IIge4JRp3jjD1mhDsZthPjzKsyegs2oFd2\n" \
"IhoPErVb9vCXdABaqboJCdBmk6yAzY3r7Ph7pLA2AMo+zqko5CtXRku+tVb379jx\n" \
"GzT+YAqLaIb7Ujm2qJAlExQj/b5YPIlv/WutajgWzbTuO5qWp+NhTZWGSaohPZC6\n" \
"VPV0jUUCgYEAmgbDtGhsaaCJWYTAu2LSW8rgJrSgUF4LAxCDJSsSko2nHXdGPfPt\n" \
"B/HiKnqdl7K9zvqKmJK42X693l5CJJi/oTHWEcjV/dLul7V1O1hp+1OD4E5otcDl\n" \
"Z/fqpFbUtNS8eRHTDNTTTHBXyi6lib2++8SuU8oLNzUKd6bESS0jZsk=\n" \
"-----END RSA PRIVATE KEY-----\n" \
;
