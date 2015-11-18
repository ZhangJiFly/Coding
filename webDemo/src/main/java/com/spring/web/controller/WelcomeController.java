package com.spring.web.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class WelcomeController {

    @RequestMapping("/welcome")
    public String welcome(Model model) {
    	String message = "<div style='text-align:center;'>"
				+ "<h3>Hello World, Spring MVC Tutorial</h3>This message is coming from CrunchifyHelloWorld.java</div>";
        model.addAttribute("message", message);
        return "welcome";
    }
}
