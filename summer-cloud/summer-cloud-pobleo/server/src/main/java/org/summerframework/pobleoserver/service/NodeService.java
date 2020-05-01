package org.summerframework.pobleoserver.service;

import org.springframework.stereotype.Service;
import org.summerframework.pobleoserver.model.Node;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

@Service
public class NodeService {
    public List<Node> nodes = new ArrayList<>();

    public void check() {
        long currentTimeStamp = new Date().getTime();
        System.out.println("Checking nodes at " + currentTimeStamp);
        for (Node node: nodes) {
            if (currentTimeStamp - node.getLastHearBeat() > 20000) {
                node.setAvailability(false);
                System.out.println("Obsolete Node: " + node.toString());
            }
        }
    }
}
