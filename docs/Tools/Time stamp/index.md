# Time Stamp

### Static Methods


| Key    | function name | input variables                                                | return       |
|--------|---------------|----------------------------------------------------------------|--------------|
| static | Date          | int Year, int Month, int Day, int Hour, int Minute, int Second | RF_TimeStamp |
| static | Date          | int Second                                                     | RF_TimeStamp |
| static | Now           | -                                                              | RF_TimeStamp |
| static | Zero          | -                                                              | RF_TimeStamp |
| public | Formatted     | -                                                              | string       |
| public | IsLowerThan   | RF_TimeStamp secondValue                                       | bool         |
| public | IsBiggerThan  | RF_TimeStamp secondValue                                       | bool         |
| public | IsEqual       | RF_TimeStamp secondValue                                       | bool         |
| public | Add           | int Day, int Hour, int Minute, int Second                      | RF_TimeStamp |
| public | SetGMT        | int GMT                                                        | bool         |
| public | GetWeekday    | -                                                              | int          |