package website.api.controller;

import java.util.List;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import website.api.dto.YorumDto;
import website.api.service.YorumService;




@RestController

@RequestMapping("/api/")
public class YorumController {

    private final YorumService yorumService;

   //@Autowired
    public YorumController(YorumService yorumService) {
        this.yorumService = yorumService;
    }

    @PostMapping("hoca/{hoca_id}/yorumlar")
    public ResponseEntity<YorumDto> createYorum(@PathVariable(value = "hoca_id") int hoca_id , @RequestBody YorumDto yorumDto){
      return new ResponseEntity<>(yorumService.createYorum(hoca_id,yorumDto), HttpStatus.CREATED);
    }

    @PutMapping("hoca/{hoca_id}/yorumlar/{id}/update")
    public ResponseEntity<YorumDto> updateYorum(@RequestBody YorumDto YorumDto , @PathVariable(value="id") int Yorum_id,@PathVariable(value = "hoca_id") int hoca_id ){
        YorumDto  response = yorumService.updateYorumById(YorumDto, Yorum_id,hoca_id);
        return new ResponseEntity<>(response,HttpStatus.OK); 
    }

    @DeleteMapping("hoca/{hoca_id}/delete/{id}")
    public ResponseEntity<String> deleteYorum(@PathVariable(value="id") int yorum_id,@PathVariable(value = "hoca_id") int hoca_id ){
         yorumService.deleteYorumById(yorum_id,hoca_id);
         return new ResponseEntity<>("Yorum silindi",HttpStatus.OK);
    }

    @GetMapping("/hoca/{hoca_id}/yorumlar")
    public List<YorumDto> getYorumByHocaId(@PathVariable (value="hoca_id")int hoca_id) {
        return yorumService.getYorumByHocaId(hoca_id);
    }
    
}
