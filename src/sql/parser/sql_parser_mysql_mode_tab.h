
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NAME_OB = 258,
     STRING_VALUE = 259,
     INTNUM = 260,
     DATE_VALUE = 261,
     TIMESTAMP_VALUE = 262,
     HINT_VALUE = 263,
     BOOL_VALUE = 264,
     APPROXNUM = 265,
     DECIMAL_VAL = 266,
     NULLX = 267,
     QUESTIONMARK = 268,
     SYSTEM_VARIABLE = 269,
     USER_VARIABLE = 270,
     CLIENT_VERSION = 271,
     MYSQL_DRIVER = 272,
     HEX_STRING_VALUE = 273,
     OUTLINE_DEFAULT_TOKEN = 274,
     KILL_EXPR = 275,
     QUERY = 276,
     CONNECTION = 277,
     LOWER_COMMA = 278,
     MINUS = 279,
     EXCEPT = 280,
     UNION = 281,
     INTERSECT = 282,
     WINDOW = 283,
     INNER = 284,
     RIGHT = 285,
     FULL = 286,
     LEFT = 287,
     CROSS = 288,
     JOIN = 289,
     SET_VAR = 290,
     OR_OP = 291,
     OR = 292,
     XOR = 293,
     AND_OP = 294,
     AND = 295,
     ELSE = 296,
     THEN = 297,
     WHEN = 298,
     CASE = 299,
     BETWEEN = 300,
     LOWER_THAN_COMP = 301,
     REGEXP = 302,
     IN = 303,
     LIKE = 304,
     IS = 305,
     COMP_NE = 306,
     COMP_LT = 307,
     COMP_LE = 308,
     COMP_GT = 309,
     COMP_GE = 310,
     P_NSEQ = 311,
     COM = 312,
     COMP_EQ = 313,
     ESCAPE = 314,
     SHIFT_RIGHT = 315,
     SHIFT_LEFT = 316,
     POW = 317,
     DIV = 318,
     MOD = 319,
     LOWER_THAN_NEG = 320,
     CNNOP = 321,
     NEG = 322,
     LOWER_PARENS = 323,
     TRANSACTION = 324,
     HIGHER_PARENS = 325,
     NOT2 = 326,
     NOT = 327,
     COLLATE = 328,
     BINARY = 329,
     INTERVAL = 330,
     LOWER_KEY = 331,
     KEY = 332,
     LOWER_ON = 333,
     ON = 334,
     LOWER_OVER = 335,
     OVER = 336,
     LOWER_INTO = 337,
     INTO = 338,
     LOWER_THAN_BY_ACCESS_SESSION = 339,
     ERROR = 340,
     PARSER_SYNTAX_ERROR = 341,
     READ_STATIC = 342,
     INDEX_HINT = 343,
     USE_NL = 344,
     FROZEN_VERSION = 345,
     TOPK = 346,
     QUERY_TIMEOUT = 347,
     READ_CONSISTENCY = 348,
     HOTSPOT = 349,
     LOG_LEVEL = 350,
     LEADING_HINT = 351,
     ORDERED = 352,
     FULL_HINT = 353,
     USE_MERGE = 354,
     USE_HASH = 355,
     NO_USE_HASH = 356,
     USE_PLAN_CACHE = 357,
     USE_JIT = 358,
     NO_USE_JIT = 359,
     NO_USE_NL = 360,
     NO_USE_MERGE = 361,
     NO_USE_BNL = 362,
     USE_NL_MATERIALIZATION = 363,
     NO_USE_NL_MATERIALIZATION = 364,
     NO_REWRITE = 365,
     TRACE_LOG = 366,
     USE_PX = 367,
     QB_NAME = 368,
     USE_HASH_AGGREGATION = 369,
     NO_USE_HASH_AGGREGATION = 370,
     NEG_SIGN = 371,
     USE_LATE_MATERIALIZATION = 372,
     NO_USE_LATE_MATERIALIZATION = 373,
     USE_BNL = 374,
     MAX_CONCURRENT = 375,
     PX_JOIN_FILTER = 376,
     NO_USE_PX = 377,
     PQ_DISTRIBUTE = 378,
     RANDOM_LOCAL = 379,
     BROADCAST = 380,
     TRACING = 381,
     MERGE_HINT = 382,
     NO_MERGE_HINT = 383,
     NO_EXPAND = 384,
     USE_CONCAT = 385,
     UNNEST = 386,
     NO_UNNEST = 387,
     PLACE_GROUP_BY = 388,
     NO_PLACE_GROUP_BY = 389,
     NO_PRED_DEDUCE = 390,
     TRANS_PARAM = 391,
     FORCE_REFRESH_LOCATION_CACHE = 392,
     LOAD_BATCH_SIZE = 393,
     NO_PX_JOIN_FILTER = 394,
     DISABLE_PARALLEL_DML = 395,
     PQ_MAP = 396,
     ENABLE_PARALLEL_DML = 397,
     NO_PARALLEL = 398,
     _BINARY = 399,
     _UTF8 = 400,
     _UTF8MB4 = 401,
     _GBK = 402,
     _UTF16 = 403,
     _GB18030 = 404,
     SELECT_HINT_BEGIN = 405,
     UPDATE_HINT_BEGIN = 406,
     DELETE_HINT_BEGIN = 407,
     INSERT_HINT_BEGIN = 408,
     REPLACE_HINT_BEGIN = 409,
     HINT_HINT_BEGIN = 410,
     HINT_END = 411,
     LOAD_DATA_HINT_BEGIN = 412,
     END_P = 413,
     DELIMITER = 414,
     ACCESSIBLE = 415,
     ADD = 416,
     ALL = 417,
     ALTER = 418,
     ANALYZE = 419,
     AS = 420,
     ASC = 421,
     ASENSITIVE = 422,
     BEFORE = 423,
     BIGINT = 424,
     BLOB = 425,
     BOTH = 426,
     BY = 427,
     CALL = 428,
     CASCADE = 429,
     CHANGE = 430,
     CHAR = 431,
     CHARACTER = 432,
     CHECK = 433,
     COLUMN = 434,
     CONDITION = 435,
     CONSTRAINT = 436,
     CONTINUE = 437,
     CONVERT = 438,
     CREATE = 439,
     CURRENT_DATE = 440,
     CURRENT_TIME = 441,
     CURRENT_TIMESTAMP = 442,
     CURRENT_USER = 443,
     CURSOR = 444,
     DATABASE = 445,
     DATABASES = 446,
     DAY_HOUR = 447,
     DAY_MICROSECOND = 448,
     DAY_MINUTE = 449,
     DAY_SECOND = 450,
     DECLARE = 451,
     DECIMAL = 452,
     DEFAULT = 453,
     DELAYED = 454,
     DELETE = 455,
     DESC = 456,
     DESCRIBE = 457,
     DETERMINISTIC = 458,
     DISTINCT = 459,
     DISTINCTROW = 460,
     DOUBLE = 461,
     DROP = 462,
     DUAL = 463,
     EACH = 464,
     ELSEIF = 465,
     ENCLOSED = 466,
     ESCAPED = 467,
     EXISTS = 468,
     EXIT = 469,
     EXPLAIN = 470,
     FETCH = 471,
     FLOAT = 472,
     FLOAT4 = 473,
     FLOAT8 = 474,
     FOR = 475,
     FORCE = 476,
     FOREIGN = 477,
     FROM = 478,
     GENERATED = 479,
     GET = 480,
     GRANT = 481,
     GROUP = 482,
     HAVING = 483,
     HIGH_PRIORITY = 484,
     HOUR_MICROSECOND = 485,
     HOUR_MINUTE = 486,
     HOUR_SECOND = 487,
     IF = 488,
     IGNORE = 489,
     INDEX = 490,
     INFILE = 491,
     INOUT = 492,
     INSENSITIVE = 493,
     INSERT = 494,
     INT = 495,
     INT1 = 496,
     INT2 = 497,
     INT3 = 498,
     INT4 = 499,
     INT8 = 500,
     INTEGER = 501,
     IO_AFTER_GTIDS = 502,
     IO_BEFORE_GTIDS = 503,
     ITERATE = 504,
     KEYS = 505,
     KILL = 506,
     LEADING = 507,
     LEAVE = 508,
     LIMIT = 509,
     LINEAR = 510,
     LINES = 511,
     LOAD = 512,
     LOCALTIME = 513,
     LOCALTIMESTAMP = 514,
     LONG = 515,
     LONGBLOB = 516,
     LONGTEXT = 517,
     LOOP = 518,
     LOW_PRIORITY = 519,
     MASTER_BIND = 520,
     MASTER_SSL_VERIFY_SERVER_CERT = 521,
     MATCH = 522,
     MAXVALUE = 523,
     MEDIUMBLOB = 524,
     MEDIUMINT = 525,
     MEDIUMTEXT = 526,
     MIDDLEINT = 527,
     MINUTE_MICROSECOND = 528,
     MINUTE_SECOND = 529,
     MODIFIES = 530,
     NATURAL = 531,
     NO_WRITE_TO_BINLOG = 532,
     OPTIMIZE = 533,
     OPTION = 534,
     OPTIONALLY = 535,
     ORDER = 536,
     OUT = 537,
     OUTER = 538,
     OUTFILE = 539,
     PARTITION = 540,
     PRECISION = 541,
     PRIMARY = 542,
     PROCEDURE = 543,
     PURGE = 544,
     RANGE = 545,
     READ = 546,
     READS = 547,
     READ_WRITE = 548,
     REAL = 549,
     REFERENCES = 550,
     RELEASE = 551,
     RENAME = 552,
     REPEAT = 553,
     REPLACE = 554,
     REQUIRE = 555,
     RESIGNAL = 556,
     RESTRICT = 557,
     RETURN = 558,
     REVOKE = 559,
     RLIKE = 560,
     SCHEMA = 561,
     SCHEMAS = 562,
     SECOND_MICROSECOND = 563,
     SELECT = 564,
     SENSITIVE = 565,
     SEPARATOR = 566,
     SET = 567,
     SHOW = 568,
     SIGNAL = 569,
     SMALLINT = 570,
     SPATIAL = 571,
     SPECIFIC = 572,
     SQL = 573,
     SQLEXCEPTION = 574,
     SQLSTATE = 575,
     SQLWARNING = 576,
     SQL_BIG_RESULT = 577,
     SQL_CALC_FOUND_ROWS = 578,
     SQL_SMALL_RESULT = 579,
     SSL = 580,
     STARTING = 581,
     STORED = 582,
     STRAIGHT_JOIN = 583,
     TABLE = 584,
     TERMINATED = 585,
     TINYBLOB = 586,
     TINYINT = 587,
     TINYTEXT = 588,
     TO = 589,
     TRAILING = 590,
     TRIGGER = 591,
     UNDO = 592,
     UNIQUE = 593,
     UNLOCK = 594,
     UNSIGNED = 595,
     UPDATE = 596,
     USAGE = 597,
     USE = 598,
     USING = 599,
     UTC_DATE = 600,
     UTC_TIME = 601,
     UTC_TIMESTAMP = 602,
     VALUES = 603,
     VARBINARY = 604,
     VARCHAR = 605,
     VARCHARACTER = 606,
     VARYING = 607,
     VIRTUAL = 608,
     WHERE = 609,
     WHILE = 610,
     WITH = 611,
     WRITE = 612,
     YEAR_MONTH = 613,
     ZEROFILL = 614,
     TABLEGROUP = 615,
     ACCESS = 616,
     ACCOUNT = 617,
     ACTION = 618,
     ACTIVE = 619,
     ADDDATE = 620,
     AFTER = 621,
     AGAINST = 622,
     AGGREGATE = 623,
     ALGORITHM = 624,
     ALWAYS = 625,
     ANALYSE = 626,
     ANY = 627,
     APPROX_COUNT_DISTINCT = 628,
     APPROX_COUNT_DISTINCT_SYNOPSIS = 629,
     APPROX_COUNT_DISTINCT_SYNOPSIS_MERGE = 630,
     ASCII = 631,
     AT = 632,
     AUTHORS = 633,
     AUTO = 634,
     AUTOEXTEND_SIZE = 635,
     AUTO_INCREMENT = 636,
     AVG = 637,
     AVG_ROW_LENGTH = 638,
     ACTIVATE = 639,
     AVAILABILITY = 640,
     ARCHIVELOG = 641,
     AUDIT = 642,
     BACKUP = 643,
     BALANCE = 644,
     BASE = 645,
     BASELINE = 646,
     BASELINE_ID = 647,
     BASIC = 648,
     BEGI = 649,
     BINDING = 650,
     BINLOG = 651,
     BIT = 652,
     BLOCK = 653,
     BLOCK_INDEX = 654,
     BLOCK_SIZE = 655,
     BLOOM_FILTER = 656,
     BOOL = 657,
     BOOLEAN = 658,
     BOOTSTRAP = 659,
     BTREE = 660,
     BYTE = 661,
     BREADTH = 662,
     BUCKETS = 663,
     BISON_LIST = 664,
     BACKUPSET = 665,
     CACHE = 666,
     CANCEL = 667,
     CASCADED = 668,
     CAST = 669,
     CATALOG_NAME = 670,
     CHAIN = 671,
     CHANGED = 672,
     CHARSET = 673,
     CHECKSUM = 674,
     CHECKPOINT = 675,
     CHUNK = 676,
     CIPHER = 677,
     CLASS_ORIGIN = 678,
     CLEAN = 679,
     CLEAR = 680,
     CLIENT = 681,
     CLOG = 682,
     CLOSE = 683,
     CLUSTER = 684,
     CLUSTER_ID = 685,
     CLUSTER_NAME = 686,
     COALESCE = 687,
     COLUMN_STAT = 688,
     CODE = 689,
     COLLATION = 690,
     COLUMN_FORMAT = 691,
     COLUMN_NAME = 692,
     COLUMNS = 693,
     COMMENT = 694,
     COMMIT = 695,
     COMMITTED = 696,
     COMPACT = 697,
     COMPLETION = 698,
     COMPRESSED = 699,
     COMPRESSION = 700,
     CONCURRENT = 701,
     CONSISTENT = 702,
     CONSISTENT_MODE = 703,
     CONSTRAINT_CATALOG = 704,
     CONSTRAINT_NAME = 705,
     CONSTRAINT_SCHEMA = 706,
     CONTAINS = 707,
     CONTEXT = 708,
     CONTRIBUTORS = 709,
     COPY = 710,
     COUNT = 711,
     CPU = 712,
     CREATE_TIMESTAMP = 713,
     CTX_ID = 714,
     CUBE = 715,
     CURDATE = 716,
     CURRENT = 717,
     CURTIME = 718,
     CURSOR_NAME = 719,
     CUME_DIST = 720,
     CYCLE = 721,
     DAG = 722,
     DATA = 723,
     DATAFILE = 724,
     DATA_TABLE_ID = 725,
     DATE = 726,
     DATE_ADD = 727,
     DATE_SUB = 728,
     DATETIME = 729,
     DAY = 730,
     DEALLOCATE = 731,
     DECRYPTION = 732,
     DEFAULT_AUTH = 733,
     DEFINER = 734,
     DELAY = 735,
     DELAY_KEY_WRITE = 736,
     DEPTH = 737,
     DES_KEY_FILE = 738,
     DENSE_RANK = 739,
     DESTINATION = 740,
     DIAGNOSTICS = 741,
     DIRECTORY = 742,
     DISABLE = 743,
     DISCARD = 744,
     DISK = 745,
     DISKGROUP = 746,
     DO = 747,
     DUMP = 748,
     DUMPFILE = 749,
     DUPLICATE = 750,
     DUPLICATE_SCOPE = 751,
     DYNAMIC = 752,
     DATABASE_ID = 753,
     DEFAULT_TABLEGROUP = 754,
     EFFECTIVE = 755,
     ENABLE = 756,
     ENCRYPTION = 757,
     END = 758,
     ENDS = 759,
     ENGINE_ = 760,
     ENGINES = 761,
     ENUM = 762,
     ENTITY = 763,
     ERROR_CODE = 764,
     ERROR_P = 765,
     ERRORS = 766,
     EVENT = 767,
     EVENTS = 768,
     EVERY = 769,
     EXCHANGE = 770,
     EXECUTE = 771,
     EXPANSION = 772,
     EXPIRE = 773,
     EXPIRE_INFO = 774,
     EXPORT = 775,
     OUTLINE = 776,
     EXTENDED = 777,
     EXTENDED_NOADDR = 778,
     EXTENT_SIZE = 779,
     EXTRACT = 780,
     EXPIRED = 781,
     EXTERNAL = 782,
     EXTERNAL_URL = 783,
     EXTERNAL_PROTOCAL = 784,
     EXTERNAL_FORMAT = 785,
     LINE_DELIMITER = 786,
     FIELD_DELIMITER = 787,
     FAILOVER = 788,
     FAST = 789,
     FAULTS = 790,
     FIELDS = 791,
     FILEX = 792,
     FINAL_COUNT = 793,
     FIRST = 794,
     FIRST_VALUE = 795,
     FIXED = 796,
     FLUSH = 797,
     FOLLOWER = 798,
     FORMAT = 799,
     FOUND = 800,
     FREEZE = 801,
     FREQUENCY = 802,
     FUNCTION = 803,
     FOLLOWING = 804,
     FLASHBACK = 805,
     FROZEN = 806,
     FILE_ID = 807,
     GENERAL = 808,
     GEOMETRY = 809,
     GEOMETRYCOLLECTION = 810,
     GET_FORMAT = 811,
     GLOBAL = 812,
     GRANTS = 813,
     GROUP_CONCAT = 814,
     GROUPING = 815,
     GTS = 816,
     GLOBAL_NAME = 817,
     GLOBAL_ALIAS = 818,
     HANDLER = 819,
     HASH = 820,
     HELP = 821,
     HISTOGRAM = 822,
     HOST = 823,
     HOSTS = 824,
     HOUR = 825,
     ID = 826,
     IDC = 827,
     IDENTIFIED = 828,
     IGNORE_SERVER_IDS = 829,
     ILOG = 830,
     IMPORT = 831,
     INCR = 832,
     INDEXES = 833,
     INDEX_TABLE_ID = 834,
     INFO = 835,
     INITIAL_SIZE = 836,
     INNODB = 837,
     INSERT_METHOD = 838,
     INSTALL = 839,
     INSTANCE = 840,
     INVOKER = 841,
     IO = 842,
     IO_THREAD = 843,
     IPC = 844,
     ISOLATE = 845,
     ISOLATION = 846,
     ISSUER = 847,
     IS_TENANT_SYS_POOL = 848,
     INVISIBLE = 849,
     MERGE = 850,
     ISNULL = 851,
     INCREMENTAL = 852,
     INNER_PARSE = 853,
     ILOGCACHE = 854,
     INPUT = 855,
     JOB = 856,
     JSON = 857,
     KEY_BLOCK_SIZE = 858,
     KEY_VERSION = 859,
     KVCACHE = 860,
     LAG = 861,
     LANGUAGE = 862,
     LAST = 863,
     LAST_VALUE = 864,
     LEAD = 865,
     LEADER = 866,
     LEAVES = 867,
     LESS = 868,
     LEAK = 869,
     LEAK_MOD = 870,
     LEAK_RATE = 871,
     LINESTRING = 872,
     LIST_ = 873,
     LISTAGG = 874,
     LOCAL = 875,
     LOCALITY = 876,
     LOCATION = 877,
     LOCKED = 878,
     LOCKS = 879,
     LOGFILE = 880,
     LOGONLY_REPLICA_NUM = 881,
     LOGS = 882,
     LOCK_ = 883,
     LOGICAL_READS = 884,
     LEVEL = 885,
     LN = 886,
     LOG = 887,
     MAJOR = 888,
     MANUAL = 889,
     MASTER = 890,
     MASTER_AUTO_POSITION = 891,
     MASTER_CONNECT_RETRY = 892,
     MASTER_DELAY = 893,
     MASTER_HEARTBEAT_PERIOD = 894,
     MASTER_HOST = 895,
     MASTER_LOG_FILE = 896,
     MASTER_LOG_POS = 897,
     MASTER_PASSWORD = 898,
     MASTER_PORT = 899,
     MASTER_RETRY_COUNT = 900,
     MASTER_SERVER_ID = 901,
     MASTER_SSL = 902,
     MASTER_SSL_CA = 903,
     MASTER_SSL_CAPATH = 904,
     MASTER_SSL_CERT = 905,
     MASTER_SSL_CIPHER = 906,
     MASTER_SSL_CRL = 907,
     MASTER_SSL_CRLPATH = 908,
     MASTER_SSL_KEY = 909,
     MASTER_USER = 910,
     MAX = 911,
     MAX_CONNECTIONS_PER_HOUR = 912,
     MAX_CPU = 913,
     MAX_DISK_SIZE = 914,
     MAX_IOPS = 915,
     MAX_MEMORY = 916,
     MAX_QUERIES_PER_HOUR = 917,
     MAX_ROWS = 918,
     MAX_SESSION_NUM = 919,
     MAX_SIZE = 920,
     MAX_UPDATES_PER_HOUR = 921,
     MAX_USER_CONNECTIONS = 922,
     MEDIUM = 923,
     MEMORY = 924,
     MEMTABLE = 925,
     MESSAGE_TEXT = 926,
     META = 927,
     MICROSECOND = 928,
     MIGRATE = 929,
     MIN = 930,
     MIN_CPU = 931,
     MIN_IOPS = 932,
     MIN_MEMORY = 933,
     MINOR = 934,
     MIN_ROWS = 935,
     MINUTE = 936,
     MODE = 937,
     MODIFY = 938,
     MONTH = 939,
     MOVE = 940,
     MULTILINESTRING = 941,
     MULTIPOINT = 942,
     MULTIPOLYGON = 943,
     MUTEX = 944,
     MYSQL_ERRNO = 945,
     MIGRATION = 946,
     MAX_USED_PART_ID = 947,
     MAXIMIZE = 948,
     MATERIALIZED = 949,
     MEMSTORE_PERCENT = 950,
     NAME = 951,
     NAMES = 952,
     NATIONAL = 953,
     NCHAR = 954,
     NDB = 955,
     NDBCLUSTER = 956,
     NEW = 957,
     NEXT = 958,
     NO = 959,
     NOAUDIT = 960,
     NODEGROUP = 961,
     NONE = 962,
     NORMAL = 963,
     NOW = 964,
     NOWAIT = 965,
     NO_WAIT = 966,
     NULLS = 967,
     NUMBER = 968,
     NVARCHAR = 969,
     NTILE = 970,
     NTH_VALUE = 971,
     NOARCHIVELOG = 972,
     NETWORK = 973,
     NOPARALLEL = 974,
     OBSOLETE = 975,
     OCCUR = 976,
     OF = 977,
     OFF = 978,
     OFFSET = 979,
     OLD_PASSWORD = 980,
     ONE = 981,
     ONE_SHOT = 982,
     ONLY = 983,
     OPEN = 984,
     OPTIONS = 985,
     ORIG_DEFAULT = 986,
     OWNER = 987,
     OLD_KEY = 988,
     PACK_KEYS = 989,
     PAGE = 990,
     PARALLEL = 991,
     PARAMETERS = 992,
     PARSER = 993,
     PARTIAL = 994,
     PARTITION_ID = 995,
     PARTITIONING = 996,
     PARTITIONS = 997,
     PASSWORD = 998,
     PAUSE = 999,
     PERCENT_RANK = 1000,
     PHASE = 1001,
     PLAN = 1002,
     PHYSICAL = 1003,
     PLANREGRESS = 1004,
     PLUGIN = 1005,
     PLUGIN_DIR = 1006,
     PLUGINS = 1007,
     POINT = 1008,
     POLYGON = 1009,
     PERFORMANCE = 1010,
     PROTECTION = 1011,
     PRIORITY = 1012,
     PL = 1013,
     POOL = 1014,
     PORT = 1015,
     POSITION = 1016,
     PREPARE = 1017,
     PRESERVE = 1018,
     PREV = 1019,
     PRIMARY_ZONE = 1020,
     PRIVILEGES = 1021,
     PROCESS = 1022,
     PROCESSLIST = 1023,
     PROFILE = 1024,
     PROFILES = 1025,
     PROXY = 1026,
     PRECEDING = 1027,
     PCTFREE = 1028,
     P_ENTITY = 1029,
     P_CHUNK = 1030,
     PRIMARY_ROOTSERVICE_LIST = 1031,
     PRIMARY_CLUSTER_ID = 1032,
     PUBLIC = 1033,
     PROGRESSIVE_MERGE_NUM = 1034,
     PS = 1035,
     QUARTER = 1036,
     QUEUE_TIME = 1037,
     QUICK = 1038,
     REBUILD = 1039,
     RECOVER = 1040,
     RECYCLE = 1041,
     REDO_BUFFER_SIZE = 1042,
     REDOFILE = 1043,
     REDUNDANT = 1044,
     REFRESH = 1045,
     REGION = 1046,
     RELAY = 1047,
     RELAYLOG = 1048,
     RELAY_LOG_FILE = 1049,
     RELAY_LOG_POS = 1050,
     RELAY_THREAD = 1051,
     RELOAD = 1052,
     REMOVE = 1053,
     REORGANIZE = 1054,
     REPAIR = 1055,
     REPEATABLE = 1056,
     REPLICA = 1057,
     REPLICA_NUM = 1058,
     REPLICA_TYPE = 1059,
     REPLICATION = 1060,
     REPORT = 1061,
     RESET = 1062,
     RESOURCE = 1063,
     RESOURCE_POOL_LIST = 1064,
     RESPECT = 1065,
     RESTART = 1066,
     RESTORE = 1067,
     RESUME = 1068,
     RETURNED_SQLSTATE = 1069,
     RETURNS = 1070,
     REVERSE = 1071,
     REWRITE_MERGE_VERSION = 1072,
     ROLLBACK = 1073,
     ROLLUP = 1074,
     ROOT = 1075,
     ROOTTABLE = 1076,
     ROOTSERVICE = 1077,
     ROOTSERVICE_LIST = 1078,
     ROUTINE = 1079,
     ROW = 1080,
     ROLLING = 1081,
     ROW_COUNT = 1082,
     ROW_FORMAT = 1083,
     ROWS = 1084,
     RTREE = 1085,
     RUN = 1086,
     RECYCLEBIN = 1087,
     ROTATE = 1088,
     ROW_NUMBER = 1089,
     RUDUNDANT = 1090,
     RECURSIVE = 1091,
     RANDOM = 1092,
     REDO_TRANSPORT_OPTIONS = 1093,
     REMOTE_OSS = 1094,
     RT = 1095,
     RANK = 1096,
     READ_ONLY = 1097,
     RECOVERY = 1098,
     SAMPLE = 1099,
     SAVEPOINT = 1100,
     SCHEDULE = 1101,
     SCHEMA_NAME = 1102,
     SCOPE = 1103,
     SECOND = 1104,
     SECURITY = 1105,
     SEED = 1106,
     SERIAL = 1107,
     SERIALIZABLE = 1108,
     SERVER = 1109,
     SERVER_IP = 1110,
     SERVER_PORT = 1111,
     SERVER_TYPE = 1112,
     SESSION = 1113,
     SESSION_USER = 1114,
     SET_MASTER_CLUSTER = 1115,
     SET_SLAVE_CLUSTER = 1116,
     SET_TP = 1117,
     SHARE = 1118,
     SHUTDOWN = 1119,
     SIGNED = 1120,
     SIMPLE = 1121,
     SLAVE = 1122,
     SLOW = 1123,
     SLOT_IDX = 1124,
     SNAPSHOT = 1125,
     SOCKET = 1126,
     SOME = 1127,
     SONAME = 1128,
     SOUNDS = 1129,
     SOURCE = 1130,
     SPFILE = 1131,
     SPLIT = 1132,
     SQL_AFTER_GTIDS = 1133,
     SQL_AFTER_MTS_GAPS = 1134,
     SQL_BEFORE_GTIDS = 1135,
     SQL_BUFFER_RESULT = 1136,
     SQL_CACHE = 1137,
     SQL_NO_CACHE = 1138,
     SQL_ID = 1139,
     SQL_THREAD = 1140,
     SQL_TSI_DAY = 1141,
     SQL_TSI_HOUR = 1142,
     SQL_TSI_MINUTE = 1143,
     SQL_TSI_MONTH = 1144,
     SQL_TSI_QUARTER = 1145,
     SQL_TSI_SECOND = 1146,
     SQL_TSI_WEEK = 1147,
     SQL_TSI_YEAR = 1148,
     STANDBY = 1149,
     STAT = 1150,
     START = 1151,
     STARTS = 1152,
     STATS_AUTO_RECALC = 1153,
     STATS_PERSISTENT = 1154,
     STATS_SAMPLE_PAGES = 1155,
     STATUS = 1156,
     STATEMENTS = 1157,
     STD = 1158,
     STDDEV = 1159,
     STDDEV_POP = 1160,
     STDDEV_SAMP = 1161,
     STRONG = 1162,
     SYNCHRONIZATION = 1163,
     STOP = 1164,
     STORAGE = 1165,
     STORAGE_FORMAT_VERSION = 1166,
     STORAGE_FORMAT_WORK_VERSION = 1167,
     STORING = 1168,
     STRING = 1169,
     SUBCLASS_ORIGIN = 1170,
     SUBDATE = 1171,
     SUBJECT = 1172,
     SUBPARTITION = 1173,
     SUBPARTITIONS = 1174,
     SUBSTR = 1175,
     SUBSTRING = 1176,
     SUCCESSFUL = 1177,
     SUM = 1178,
     SUPER = 1179,
     SUSPEND = 1180,
     SWAPS = 1181,
     SWITCH = 1182,
     SWITCHES = 1183,
     SWITCHOVER = 1184,
     SYSTEM = 1185,
     SYSTEM_USER = 1186,
     SYSDATE = 1187,
     SESSION_ALIAS = 1188,
     SYNONYM = 1189,
     SIZE = 1190,
     TABLE_CHECKSUM = 1191,
     TABLE_MODE = 1192,
     TABLE_ID = 1193,
     TABLE_NAME = 1194,
     TABLEGROUPS = 1195,
     TABLES = 1196,
     TABLESPACE = 1197,
     TABLET = 1198,
     TABLET_MAX_SIZE = 1199,
     TEMPLATE = 1200,
     TEMPORARY = 1201,
     TEMPTABLE = 1202,
     TENANT = 1203,
     TEXT = 1204,
     THAN = 1205,
     TIME = 1206,
     TIMESTAMP = 1207,
     TIMESTAMPADD = 1208,
     TIMESTAMPDIFF = 1209,
     TP_NO = 1210,
     TP_NAME = 1211,
     TRACE = 1212,
     TRADITIONAL = 1213,
     TRIGGERS = 1214,
     TRIM = 1215,
     TRUNCATE = 1216,
     TYPE = 1217,
     TYPES = 1218,
     TASK = 1219,
     TABLET_SIZE = 1220,
     TABLEGROUP_ID = 1221,
     TENANT_ID = 1222,
     THROTTLE = 1223,
     TIME_ZONE_INFO = 1224,
     UNCOMMITTED = 1225,
     UNDEFINED = 1226,
     UNDO_BUFFER_SIZE = 1227,
     UNDOFILE = 1228,
     UNICODE = 1229,
     UNINSTALL = 1230,
     UNIT = 1231,
     UNIT_NUM = 1232,
     UNLOCKED = 1233,
     UNTIL = 1234,
     UNUSUAL = 1235,
     UPGRADE = 1236,
     USE_BLOOM_FILTER = 1237,
     UNKNOWN = 1238,
     USE_FRM = 1239,
     USER = 1240,
     USER_RESOURCES = 1241,
     UNBOUNDED = 1242,
     VALID = 1243,
     VALUE = 1244,
     VARIANCE = 1245,
     VARIABLES = 1246,
     VERBOSE = 1247,
     VERIFY = 1248,
     VIEW = 1249,
     VISIBLE = 1250,
     VIRTUAL_COLUMN_ID = 1251,
     VALIDATE = 1252,
     VAR_POP = 1253,
     VAR_SAMP = 1254,
     WAIT = 1255,
     WARNINGS = 1256,
     WEEK = 1257,
     WEIGHT_STRING = 1258,
     WHENEVER = 1259,
     WITH_ROWID = 1260,
     WORK = 1261,
     WRAPPER = 1262,
     WEAK = 1263,
     X509 = 1264,
     XA = 1265,
     XML = 1266,
     YEAR = 1267,
     ZONE = 1268,
     ZONE_LIST = 1269,
     ZONE_TYPE = 1270,
     COMP_NSEQ = 1271,
     COMMA = 1272
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 23 "../../../src/sql/parser/sql_parser_mysql_mode.y"

  struct _ParseNode *node;
  const struct _NonReservedKeyword *non_reserved_keyword;
  const struct _NonReservedKeyword *reserved_keyword;
  int32_t ival[2]; //ival[0] means value,
                   //ival[1] means the number of constants that fast parse can recognize in the corresponding node and its child nodes,
                   //ival[2] for length_semantics
 


/* Line 1676 of yacc.c  */
#line 1080 "../../../src/sql/parser/sql_parser_mysql_mode_tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif



#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



