package website.api.service.implementation;

import java.util.List;
import java.util.stream.Collectors;

import org.springframework.stereotype.Service;

import website.api.dto.HocaDto;
import website.api.exceptions.HocaNotFoundException;
import website.api.model.Hoca;
import website.api.repository.HocaRepository;
import website.api.service.HocaService;

@Service
public class HocaServiceImpl implements HocaService {
        
    private final HocaRepository hocaRepository;

   
    public HocaServiceImpl(HocaRepository hocaRepository) {
        this.hocaRepository = hocaRepository;
    }
    
    
    @Override
    public HocaDto createHoca(HocaDto hocaDto){
        Hoca hoca = new Hoca();
        hoca.setName(hocaDto.getName());

        Hoca newHoca = hocaRepository.save(hoca);
        HocaDto hocaResponse = new HocaDto();
        hocaResponse.setId(newHoca.getId());
        hocaResponse.setName(newHoca.getName());
        return hocaResponse;    
    }


    @Override
    public List<HocaDto> getAllHocas() {
       List<Hoca> hoca = hocaRepository.findAll();
       return hoca.stream().map(h -> mapToDto(h)).collect(Collectors.toList());
    }

    private HocaDto mapToDto(Hoca hoca){
        HocaDto hocaDto = new HocaDto();
        hocaDto.setId(hoca.getId());
        hocaDto.setName(hoca.getName());
        return hocaDto;
    }
    private Hoca mapToEntity(HocaDto hocaDto){
        Hoca hoca = new Hoca();
        hoca.setId(hocaDto.getId());
        hoca.setName(hocaDto.getName());
        return hoca;
    }


    @Override
    public HocaDto getHocaById(int id) {
        Hoca hoca = hocaRepository.findById(id).orElseThrow(()-> new HocaNotFoundException("Hoca bulunamadı"));
        return mapToDto(hoca);
    } 

    @Override
    public HocaDto updateHocaById(HocaDto hocaDto , int id ) { 
        Hoca hoca = hocaRepository.findById(id).orElseThrow(()-> new HocaNotFoundException("Hoca güncellenemedi"));
        hoca.setName(hocaDto.getName());
        hocaRepository.save(hoca);
        return mapToDto(hoca);
    }


    @Override
    public void deleteHocaById(int id) {
        Hoca hoca = hocaRepository.findById(id).orElseThrow(()-> new HocaNotFoundException("Silmek istediğiniz hoca mevcut değil"));
        hocaRepository.delete(hoca);
    }
}
