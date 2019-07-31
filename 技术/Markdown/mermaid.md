---
title: mermaid
date: 2018-01-27 11:21:30
tags: [mermaid, markdown]
categories: [markdown]
---

mermaid 语法示例


``` mermaid
graph TD;
    A-->B;
    B-->C;
    C-->D;

    A[收到箱子打开信号]
    B[生成运动指令<5ms]
    C[生成机械手动作500-1000ms]
    D[运动1000-2000ms]
```

``` mermaid
graph TD;
    A-->B;
    B-->C;
    C-->D;
    D-->E;
    E--成功-->F
    F-->G
    E--失败-->H
    H-->I

    A[收到箱子预处理信号]
    B[生成运动指令<5ms]
    C[生成机械手预处理动作500-600ms]
    D[运动500-1000ms]
    E[等待箱子开启状态]
    F[生成机械手后续处理动作500-600ms]
    G[运动500-1000ms]
    H[超时判断10000-20000ms]
    I[重置机械手状态10ms]
```

<!-- more -->

``` mermaid
graph TD;
    A-->B;
    A-->C;
    B-->D;
    C-->D;
```

``` mermaid
graph TD
    A[INPUT] --> B{str.length > 23 ?}
    B--true-->C{result success ?}
    C--true-->T
    C--false-->F
    B--false-->D[write log]
    D-->T
    F[FALSE]
    T[TRUE]
```

``` mermaid
sequenceDiagram
    participant Alice
    participant Bob
    Alice->John: Hello John, how are you?
    loop Healthcheck
        John->John: Fight against hypochondria
    end
    Note right of John: Rational thoughts <br/>prevail...
    John-->Alice: Great!
    John->Bob: How about you?
    Bob-->John: Jolly good!
```

``` mermaid
gantt
    dateFormat  YYYY-MM-DD
    title Adding GANTT diagram functionality to mermaid
    section A section
    Completed task            :done,    des1, 2014-01-06,2014-01-08
    Active task               :active,  des2, 2014-01-09, 3d
    Future task               :         des3, after des2, 5d
    Future task2               :         des4, after des3, 5d
    section Critical tasks
    Completed task in the critical line :crit, done, 2014-01-06,24h
    Implement parser and jison          :crit, done, after des1, 2d
    Create tests for parser             :crit, active, 3d
    Future task in critical line        :crit, 5d
    Create tests for renderer           :2d
    Add to mermaid                      :1d
```

``` mermaid
graph LR
    test((测试程序)) ==> client((客户端))
    client ==> server((中控程序))
    class test,client green
```


``` mermaid
graph TB
    sq[Square shape] --> ci((Circle shape))

    subgraph A subgraph
        od>Odd shape]-- Two line<br/>edge comment --> ro
        di{Diamond with <br/> line break} -.-> ro(Rounded<br>square<br>shape)
        di==>ro2(Rounded square shape)
    end

    %% Notice that no text in shape are added here instead that is appended further down
    e --> od3>Really long text with linebreak<br>in an Odd shape]

    cyr[Cyrillic]-->cyr2((Circle shape Начало));

    %% Comments after double percent signs
    e((Inner / circle<br>and some odd <br>special characters)) --> f(,.?!+-*ز)
    
    classDef green fill:#9f6,stroke:#333,stroke-width:2px;
    classDef orange fill:#f96,stroke:#333,stroke-width:4px;
    class sq,e green
    class di orange
```


``` mermaid
gantt
        dateFormat DD-MM-YYYY
        title ScalarCell
        section 正集源项目
        上线    :active,    des1, 2017-11-06,2018-02-11
        验证阶段    :active,    des2, 2018-01-09, 13d
```

``` mermaid
gantt
        dateFormat  YYYY-MM-DD
        title Adding GANTT diagram functionality to mermaid
        section A section
        Completed task            :done,    des1, 2014-01-06,2014-01-08
        Active task               :active,  des2, 2014-01-09, 3d
```


