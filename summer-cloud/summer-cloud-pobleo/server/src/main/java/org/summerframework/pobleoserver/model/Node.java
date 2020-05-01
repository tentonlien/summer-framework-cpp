package org.summerframework.pobleoserver.model;

import lombok.Data;

@Data
public class Node {
    private String name;
    private String host;
    private boolean availability;
    private String time;
    private long lastHearBeat;

    public Node() {}

    public Node(String name, String host, boolean availability, String time, long lastHeartBeat) {
        this.name = name;
        this.host = host;
        this.availability = availability;
        this.time = time;
        this.lastHearBeat = lastHeartBeat;

    }
}
