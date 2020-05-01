package org.summerframework.pobleoserver.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.summerframework.pobleoserver.model.Node;
import org.summerframework.pobleoserver.service.NodeService;

import java.util.Date;

@RestController
public class ServiceController {

    @Autowired
    private NodeService nodeService;

    @PostMapping("/register")
    public String update(@RequestBody Node heartBeatNode) {
        for (Node node: nodeService.nodes) {
            if (heartBeatNode.getName().equals(node.getName())) {
                if (heartBeatNode.getHost().equals(node.getHost())) {
                    node.setLastHearBeat(new Date().getTime());
                    node.setAvailability(true);
                    return "SUCCESS";
                }
            }
        }
        heartBeatNode.setAvailability(true);
        heartBeatNode.setTime(new Date().toString());
        heartBeatNode.setLastHearBeat(new Date().getTime());
        nodeService.nodes.add(heartBeatNode);
        return "SUCCESS";
    }
}
