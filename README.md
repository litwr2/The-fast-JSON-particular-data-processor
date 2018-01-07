# The fast JSON particular data processor

We have a directory containing N log-files (for example, 10) named _fileM.log_.  The numbering is one-based.  Every log-file contains a lot of records (for example, more than 1000).  Every record presents a player action.  The records are json-formatted:

```json
{
    "ts_fact" : 1489494303,
    "fact_name": "fact1",
    "actor_id": 111222,
    "props": {
        "prop1": 11,
        "prop2": 22,
        ...
        "prop10": 1010,
    }
}
```

The field meanings:

* ts_fact: when the action was done, timestamp, uint32;

* fact_name: name of the action, string;

* actor_id: the action's author, uint32;

* props: the action's property.

The application reads all log-files in the directory and fills the next structure: for every timestamp (UTC+0), for every fact name, for every property list (prop1, .., prop10) is kept number of those facts in the log-files.

The result of log processing writes to a file _agr.txt_ which may have an arbitrary format.

For the processing acceleration the application uses multithreading (for example, to process every log-file with a thread).

The application takes the next parameters (they can be constants in the application program text):

* a full path to the log-file directory;

* a number of the logs in the directory;

* a number of threads.

The number of records in the log-files are above 10000.

The program _serv-list2.cpp_ uses a forward list to make the task.  The program _serv-map.cpp_ does the same but uses a map instead.  The program _generate-log-files.cpp_ may be used to generate the random log-files.

