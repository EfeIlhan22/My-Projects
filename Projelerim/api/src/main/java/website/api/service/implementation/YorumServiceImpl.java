package website.api.service.implementation;

import java.util.List;
import java.util.stream.Collectors;

import org.springframework.stereotype.Service;

import website.api.dto.YorumDto;
import website.api.exceptions.HocaNotFoundException;
import website.api.exceptions.YorumNotFoundException;
import website.api.model.Hoca;
import website.api.model.Yorum;
import website.api.repository.HocaRepository;
import website.api.repository.YorumRepository;
import website.api.service.YorumService;


@Service
public class YorumServiceImpl implements YorumService {
    
    private final  YorumRepository yorumRepository;
    private final HocaRepository hocaRepository;

    //@Autowirred
    public YorumServiceImpl(YorumRepository yorumRepository,HocaRepository hocaRepository) {
        this.yorumRepository = yorumRepository;
        this.hocaRepository = hocaRepository;   
    }

    @Override
    public YorumDto createYorum(int hoca_id,YorumDto yorumDto) {
       Yorum yorum = maptoYorum(yorumDto);
       Hoca hoca = hocaRepository.findById(hoca_id).orElseThrow(() -> new HocaNotFoundException("İlintili hoca bulunamadı"));

       yorum.setHoca(hoca);

       Yorum newYorum = yorumRepository.save(yorum);

       return maptoDto(newYorum);
    }

    @Override
    public YorumDto updateYorumById(YorumDto yorumDto, int yorum_id,int hoca_id) {
       Hoca hoca = hocaRepository.findById(hoca_id).orElseThrow(() -> new HocaNotFoundException("Aradığnız hoca bulunamadı"));

       Yorum yorum = yorumRepository.findById(yorum_id).orElseThrow(() -> new YorumNotFoundException("Aradığnız yorum bulunamadı"));
    
       if(yorum.getHoca().getId() != hoca.getId()) {
        throw new YorumNotFoundException("Bu yorum bu hocaya ait değil!");
    }
        yorum.setNefretsebebi(yorumDto.getNefretsebebi());
        yorum.setYorum(yorumDto.getYorum());


        Yorum updateYorum = yorumRepository.save(yorum);
        return maptoDto(updateYorum);
    }

    @Override
    public void deleteYorumById(int yorum_id,int hoca_id) {
       Hoca hoca = hocaRepository.findById(hoca_id).orElseThrow(() -> new HocaNotFoundException("Aradığnız hoca bulunamadı"));

       Yorum yorum = yorumRepository.findById(yorum_id).orElseThrow(() -> new YorumNotFoundException("Aradığınız yorum bulunamadı"));
    
       if(yorum.getHoca().getId() != hoca.getId()) {
        throw new YorumNotFoundException("Bu yorum bu hocaya ait değil!");
    }
        yorumRepository.delete(yorum);
    }

    private YorumDto maptoDto(Yorum yorum) {
        YorumDto yorumDto = new YorumDto();

        yorumDto.setId(yorum.getId());
        yorumDto.setUsername(yorum.getUsername());
        yorumDto.setNefretsebebi(yorum.getNefretsebebi());
        yorumDto.setPhoto_data_path(yorum.getPhoto_data_path());
        yorumDto.setStartTime(yorum.getStartTime());
        yorumDto.setYorum(yorum.getYorum());
        yorumDto.setLike_count(yorum.getLike_count());

        return yorumDto;
    }

    private Yorum maptoYorum(YorumDto yorumDto){
        Yorum yorum = new Yorum();
        yorum.setUsername(yorumDto.getUsername());
        yorum.setNefretsebebi(yorumDto.getNefretsebebi());
        yorum.setPhoto_data_path(yorumDto.getPhoto_data_path());
        yorum.setStartTime(yorumDto.getStartTime());
        yorum.setYorum(yorumDto.getYorum());
        yorum.setLike_count(yorumDto.getLike_count());
        return yorum;
    }

    @Override
    public List<YorumDto> getYorumByHocaId(int id) {
        List<Yorum> yorums = yorumRepository.findByHocaId(id);
        return yorums.stream().map(yorum->maptoDto(yorum)).collect(Collectors.toList());
    }
}
