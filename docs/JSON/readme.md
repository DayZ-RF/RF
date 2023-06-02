# JSONService

JSON Serialization service helper.

## Read File

```csharp

string filename = "/path/to/file.json";
ClassName classObject;
JSONService<ClassName>.ReadFile(filename, classObject);

```

## Write File

```csharp

string filename = "/path/to/file.json";
ClassName classObject = new ClassName();
// ... filling classObject
JSONService<ClassName>.WriteFile(filename, classObject);

```

## Read String

```csharp

string jsonString = "{\"property\": \"value\"}";
ClassName classObject = JSONService<ClassName>.ReadString(jsonString);

```

## Write String

```csharp

ClassName classObject = new ClassName();
// ... filling classObject
string result = JSONService<ClassName>.WriteString(jsonString);

```
