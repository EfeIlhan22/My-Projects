package website.api.controller;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;

import website.api.dto.YorumDto;
import website.api.dto.YorumResponse;
import website.api.service.YorumService;



@RestController

@RequestMapping("/api/")
public class YorumController {

    private final YorumService yorumService;

   //@Autowired
    public YorumController(YorumService yorumService) {
        this.yorumService = yorumService;
    }




    @GetMapping("yorum")
    public ResponseEntity <YorumResponse> getYorums(
        @RequestParam(value = "pageNo", defaultValue = "0", required = false) int pageNo,
            @RequestParam(value = "pageSize", defaultValue = "10", required = false) int pageSize
        ){ 
        return new ResponseEntity<>(yorumService.getAllYorums(pageNo,pageSize) , HttpStatus.OK);
    }
    
    @GetMapping("yorum/{id}")
    public ResponseEntity<YorumDto> YorumDetail(@PathVariable int id){
        return  ResponseEntity.ok(yorumService.getYorumById(id));
    }

    @PostMapping("yorum/create")
    @ResponseStatus(HttpStatus.CREATED)
    public ResponseEntity<YorumDto> createYorum(@RequestBody YorumDto YorumDto){
      return new ResponseEntity<>(yorumService.createYorum(YorumDto), HttpStatus.CREATED);
    }

    @PutMapping("yorum/{id}/update")
    public ResponseEntity<YorumDto> updateYorum(@RequestBody YorumDto YorumDto , @PathVariable("id") int Yorum_id){
        YorumDto  response = yorumService.updateYorumById(YorumDto, Yorum_id);
        return new ResponseEntity<>(response,HttpStatus.OK); 
    }

    @DeleteMapping("Yorum/{id}/delete")
    public ResponseEntity<String> deleteYorum(@PathVariable("id") int yorum_id){
         yorumService.deleteYorumById(yorum_id);
         return new ResponseEntity<>("Yorum silindi",HttpStatus.OK);
    }
}
