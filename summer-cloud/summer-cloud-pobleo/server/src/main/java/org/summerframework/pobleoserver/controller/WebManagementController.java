package org.summerframework.pobleoserver.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.summerframework.pobleoserver.model.Node;
import org.summerframework.pobleoserver.service.NodeService;
import org.summerframework.pobleoserver.util.FileUtil;

import java.util.Date;
import java.util.List;

@Controller
public class WebManagementController {

    @Autowired
    private NodeService nodeService;

    @GetMapping("/")
    public String index(ModelMap modelMap) {
        nodeService.check();
        modelMap.addAttribute("currentTime", new Date());
        //nodeService.nodes.add(new Node("NODE-" + nodeService.nodes.size(), "127.0.0.1:7070", nodeService.nodes.size() % 2 == 0, new Date().toString(), "234"));
        modelMap.addAttribute("nodes", nodeService.nodes);
        return "index";
    }
}
