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
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;

import lombok.RequiredArgsConstructor;
import website.api.dto.HocaDto;
import website.api.service.HocaService;



@RestController
@RequiredArgsConstructor

@RequestMapping("/api/")
public class HocaController {

    private final HocaService hocaService;






    @GetMapping("hoca")
    public ResponseEntity <List<HocaDto>> getHocas(){
        return new ResponseEntity<>(hocaService.getAllHocas() , HttpStatus.OK);
    }
    
    @GetMapping("hoca/{id}")
    public ResponseEntity<HocaDto> hocaDetail(@PathVariable int id){
        return  ResponseEntity.ok(hocaService.getHocaById(id));
    }

    @PostMapping("hoca/create")
    @ResponseStatus(HttpStatus.CREATED)
    public ResponseEntity<HocaDto> createHoca(@RequestBody HocaDto hocaDto){
      return new ResponseEntity<>(hocaService.createHoca(hocaDto), HttpStatus.CREATED);
    }

    @PutMapping("hoca/{id}/update")
    public ResponseEntity<HocaDto> updateHoca(@RequestBody HocaDto hocaDto , @PathVariable("id") int hoca_id){
        HocaDto  response = hocaService.updateHocaById(hocaDto, hoca_id);
        return new ResponseEntity<>(response,HttpStatus.OK); 
    }

    @DeleteMapping("hoca/{id}/delete")
    public ResponseEntity<String> deleteHoca(@PathVariable("id") int hoca_id){
         hocaService.deleteHocaById(hoca_id);
         return new ResponseEntity<>("Hoca silindi",HttpStatus.OK);
    }
}
