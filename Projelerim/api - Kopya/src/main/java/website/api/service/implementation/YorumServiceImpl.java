package website.api.service.implementation;

import java.util.List;
import java.util.stream.Collectors;

import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

import website.api.dto.YorumDto;
import website.api.dto.YorumResponse;
import website.api.exceptions.YorumNotFoundException;
import website.api.model.Yorum;
import website.api.repository.YorumRepository;
import website.api.service.YorumService;


@Service
public class YorumServiceImpl implements YorumService {
    
    private final YorumRepository yorumRepository;


    public YorumServiceImpl(YorumRepository yorumRepository) {
        this.yorumRepository = yorumRepository;
    }

    @Override
    public YorumDto createYorum(YorumDto yorumDto) {
       Yorum yorum = new Yorum();
       yorum.setUsername(yorumDto.getUsername());
       yorum.setNefretsebebi(yorumDto.getNefretsebebi());
       yorum.setPhoto_data_path(yorumDto.getPhoto_data_path());
       yorum.setStartTime(yorumDto.getStartTime());
       yorum.setYorum(yorumDto.getYorum());
       yorum.setLike_count(yorumDto.getLike_count());
       
       Yorum newYorum= yorumRepository.save(yorum);
       YorumDto yorumResponse = new YorumDto();
       yorumResponse.setUsername(newYorum.getUsername());
       yorumResponse.setNefretsebebi(newYorum.getNefretsebebi());
       yorumResponse.setPhoto_data_path(newYorum.getPhoto_data_path());
       yorumResponse.setStartTime(newYorum.getStartTime());
       yorumResponse.setYorum(newYorum.getYorum());
       yorumResponse.setLike_count(newYorum.getLike_count());

       return yorumResponse;
    }

    @Override
    public YorumResponse getAllYorums(int pageNo,int pageSize) {
        Pageable pageable = PageRequest.of(pageNo, pageSize);
        Page<Yorum> yorums = yorumRepository.findAll(pageable);
        List<Yorum> listOfYorums = yorums.getContent();
        List<YorumDto> content = listOfYorums.stream().map(y->maptoDto(y)).collect(Collectors.toList());

        YorumResponse yorumResponse = new YorumResponse();
        yorumResponse.setContent(content);
        yorumResponse.setPageNumber(yorums.getNumber());
        yorumResponse.setPageSize(yorums.getSize());
        yorumResponse.setTotalElements(yorums.getNumberOfElements());
        yorumResponse.setTotalPages(yorums.getTotalPages());
        yorumResponse.setLast(yorums.isLast());
        return yorumResponse;
    }

    @Override
    public YorumDto getYorumById(int id) {
        Yorum yorum = yorumRepository.findById(id).orElseThrow(()-> new YorumNotFoundException("Yorum bulunamadı"));
        return maptoDto(yorum);
    }

    @Override
    public YorumDto updateYorumById(YorumDto yorumDto, int id) {
        Yorum yorum = yorumRepository.findById(id).orElseThrow(()-> new YorumNotFoundException("Güncellemek istediğiniz yorum bulunamadı"));
        
        yorum.setUsername(yorumDto.getUsername());
        yorum.setNefretsebebi(yorumDto.getNefretsebebi());
        yorum.setPhoto_data_path(yorumDto.getPhoto_data_path());
        yorum.setStartTime(yorumDto.getStartTime());
        yorum.setYorum(yorumDto.getYorum());
        yorum.setLike_count(yorumDto.getLike_count());
        
        return maptoDto(yorum);
    }

    @Override
    public void deleteYorumById(int id) {
        Yorum yorum = yorumRepository.findById(id).orElseThrow(()-> new YorumNotFoundException("Silmek istediğiniz yorum bulunamadı"));
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
}
